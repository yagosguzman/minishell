/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:15:05 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/19 16:53:48 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_inout	*init_inout(t_comand **cmds)
{
	t_inout	*redir;

	if ((*cmds)->redir == NULL)
	{
		(*cmds)->redir = (t_inout *)ft_calloc(sizeof(t_inout), 1);
		if (!(*cmds)->redir)
			ft_error("error init struct\n", 1);
		redir = (*cmds)->redir;
	}
	else
	{
		redir = (*cmds)->redir;
		while (redir->next != NULL)
			redir = redir->next;
		redir->next = (t_inout *)malloc(sizeof(t_inout));
		if (!redir->next)
			ft_error("error init struct\n", 1);
		redir = redir->next;
	}
	redir->next = NULL;
	redir->file = NULL;
	redir->type = -1;
	return (redir);
}

void	init_cmd(t_comand *cmd)
{
	cmd->next = NULL;
	cmd->before = NULL;
	cmd->pipe_line = 0;
	cmd->arg = NULL;
	cmd->num_arg = 0;
	cmd->redir = NULL;
	cmd->path = NULL;
	cmd->envp = NULL;
}

t_comand	*create_cmd(void)
{
	t_comand	*cmd;

	cmd = malloc(sizeof(t_comand));
	if (!cmd)
		return (0);
	init_cmd(cmd);
	return (cmd);
}

t_comand	*newcmd(t_comand *old)
{
	t_comand	*new;

	new = create_cmd();
	old->next = new;
	new->before = old;
	new->pipe_line = old->pipe_line + 1;
	return (new);
}
