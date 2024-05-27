/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:04:49 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/19 16:39:21 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_close_fd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

int	aux_check_path(t_comand *cmd, char *path)
{
	path = path_searcher(cmd);
	if (path == NULL)
		return (127);
	cmd->path = path;
	return (0);
}

int	is_file_dir(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	exit_status(int *status)
{
	if (WIFEXITED(*status))
		g_status = (WEXITSTATUS(*status));
	else if (WIFSIGNALED(*status))
	{
		if (WTERMSIG(*status) == SIGINT)
			g_status = 130;
		else if (WTERMSIG(*status) == SIGQUIT)
		{
			g_status = 131;
			ft_printf("Quit: 3\n");
		}
	}
	else if (WIFSTOPPED(*status))
		g_status = WSTOPSIG(*status);
	else
		g_status = (WTERMSIG(*status));
}

char	**path_searcher_loop(char **split_path, t_env *iter_env, t_comand *cmd)
{
	while (iter_env && split_path == NULL)
	{
		if (ft_strncmp("PATH", iter_env->name, ft_strlen("PATH") + 1) == 0
			&& cmd->arg[0][0] != '.')
			split_path = magic_split(iter_env->value, ':', cmd->arg[0]);
		else
			iter_env = iter_env->next;
	}
	return (split_path);
}
