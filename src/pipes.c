/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 19:45:26 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/21 17:54:17 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipe	*init_pipe_s(t_comand *cmd)
{
	t_comand	*aux;
	t_pipe		*pipe_s;

	pipe_s = NULL;
	pipe_s = ft_calloc(sizeof(t_pipe), 1);
	if (!pipe_s)
		return (NULL);
	aux = cmd;
	while (aux->next)
		aux = aux->next;
	pipe_s->pid = ft_calloc(sizeof(pid_t), aux->pipe_line + 1);
	if (!pipe_s->pid)
	{
		free(pipe_s);
		return (NULL);
	}
	return (pipe_s);
}

void	free_pipe_s(t_pipe **pipe_s)
{
	if (pipe_s[0]->pid)
		free(pipe_s[0]->pid);
	free (pipe_s[0]);
}

void	set_dup2(t_pipe *pipe_s, int i)
{
	if (i == 1)
	{
		if (dup2(pipe_s->fd[1], STDOUT_FILENO) < 0)
		{
			ft_close_fd(pipe_s->fd);
			exit(g_status);
		}
		ft_close_fd(pipe_s->fd);
	}
	else
	{
		if (dup2(pipe_s->fd[0], STDIN_FILENO) < 0)
		{
			ft_close_fd(pipe_s->fd);
			exit(g_status);
		}
		ft_close_fd(pipe_s->fd);
	}
}
