/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:37:35 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/19 22:20:29 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_redirs(t_comand **cmds)
{
	t_inout	*aux;

	while (cmds[0]->redir)
	{
		aux = cmds[0]->redir->next;
		if (cmds[0]->redir->file)
			free(cmds[0]->redir->file);
		free (cmds[0]->redir);
		cmds[0]->redir = aux;
	}
}

void	free_cmds(t_comand **cmds)
{
	t_comand	*aux;
	int			i;

	i = 0;
	while (cmds[0])
	{
		i = 0;
		aux = cmds[0]->next;
		while (i < cmds[0]->num_arg)
			free(cmds[0]->arg[i++]);
		if (i > 0)
			free(cmds[0]->arg[i]);
		if (cmds[0]->arg)
			free(cmds[0]->arg);
		if (cmds[0]->redir)
			free_redirs(cmds);
		if (cmds[0]->envp)
			free_words(&cmds[0]->envp);
		if (cmds[0]->path)
			free(cmds[0]->path);
		if (cmds[0])
			free(cmds[0]);
		cmds[0] = aux;
	}
}

void	free_words(char ***words)
{
	int	i;

	i = 0;
	if (words[0][i])
	{
		while (words[0][i])
			free(words[0][i++]);
		free(words[0][i]);
	}
	free(words[0]);
}

void	*free_aux_struc(t_aux **aux)
{
	if (aux[0]->name)
		free(aux[0]->name);
	if (aux[0]->arg)
		free(aux[0]->arg);
	if (aux[0]->expand)
		free(aux[0]->expand);
	if (aux[0])
		free(aux[0]);
	return (NULL);
}
