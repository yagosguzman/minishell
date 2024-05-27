/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 18:16:11 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/23 20:20:28 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_executor(t_comand *cmd, t_pipe *pipe_s)
{
	int		result;
	char	*path;

	path = NULL;
	result = check_builtin(cmd->arg[0]);
	if (result >= 0)
	{
		g_status = exec_builtin(cmd, result, pipe_s);
		return (1);
	}
	else if (access(cmd->arg[0], F_OK) == 0)
	{
		if (access(cmd->arg[0], X_OK) == 0)
			cmd->path = ft_strdup(cmd->arg[0]);
		else
		{
			ft_error(cmd->arg[0], 126);
			return (ft_error(": Permission denied\n", 126));
		}
	}
	else
		if (aux_check_path(cmd, path) == 127)
			return (ft_error("", 127));
	return (0);
}

void	single_cmd(t_comand *cmd, t_pipe *pipe_s)
{
	int	status;
	int	check;

	g_status = 0;
	status = -1;
	g_status = set_heredoc(cmd, pipe_s);
	g_status = set_redir(cmd);
	check = check_executor(cmd, pipe_s);
	if (g_status != 1 && (check == 0 || check == 127))
	{
		wait_signal(0);
		pipe_s->pid[0] = fork();
		if (pipe_s->pid[0] == 0)
		{
			execve(cmd->path, cmd->arg, cmd->envp);
			exit(127);
		}
		waitpid(pipe_s->pid[0], &status, 0);
		exit_status(&status);
	}
	remove_heredoc(cmd);
	dup2((*pipe_s).og_fd[0], STDIN_FILENO);
	dup2((*pipe_s).og_fd[1], STDOUT_FILENO);
	ft_close_fd((*pipe_s).og_fd);
}

void	child_process(t_comand *cmd, t_pipe *pipe_s)
{
	int	check;

	wait_signal(0);
	if (cmd->next)
		set_dup2(pipe_s, 1);
	g_status = set_redir(cmd);
	check = check_executor(cmd, pipe_s);
	if (g_status != 1 && (check == 0 || check == 127))
		execve(cmd->path, cmd->arg, cmd->envp);
	exit(127);
}

void	executor_loop(t_comand *cmd, t_pipe *pipe_s, int *n_process)
{
	t_comand	*aux;

	aux = cmd;
	while (cmd)
	{
		g_status = 0;
		if (cmd->next)
			if (pipe(pipe_s->fd) < 0)
				ft_exit(&cmd, &pipe_s);
		if (g_status != 1)
		{
			g_status = set_heredoc(cmd, pipe_s);
			(*n_process)++;
			pipe_s->pid[(*n_process) - 1] = fork();
			if (pipe_s->pid[(*n_process) - 1] < 0)
				ft_exit(&cmd, &pipe_s);
			if (pipe_s->pid[(*n_process) - 1] == 0)
				child_process(cmd, pipe_s);
			if (cmd->next)
				set_dup2(pipe_s, 0);
		}
		cmd = cmd->next;
	}
	cmd = aux;
}

int	executor(t_comand *cmd, t_pipe *pipe_s)
{
	int		status;
	int		n_process;
	int		i;

	i = 0;
	n_process = 0;
	status = -1;
	pipe_s->og_fd[0] = dup(STDIN_FILENO);
	pipe_s->og_fd[1] = dup(STDOUT_FILENO);
	if (!cmd->next)
		single_cmd(cmd, pipe_s);
	else
	{
		wait_signal(0);
		executor_loop(cmd, pipe_s, &n_process);
		dup2(pipe_s->og_fd[0], STDIN_FILENO);
		dup2(pipe_s->og_fd[1], STDOUT_FILENO);
		ft_close_fd(pipe_s->og_fd);
		while (n_process > i)
			waitpid(pipe_s->pid[i++], &status, 0);
		remove_heredoc(cmd);
		if (status != -1)
			exit_status(&status);
	}
	return (0);
}
