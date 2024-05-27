/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 17:24:53 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/23 19:36:59 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	remove_heredoc(t_comand *cmds)
{
	t_comand	*aux_cmd;
	t_inout		*aux;
	char		*aux_char;

	aux_cmd = cmds;
	while (aux_cmd)
	{
		aux = aux_cmd ->redir;
		while (aux)
		{
			if (aux->type == HEREDOC)
			{
				aux_char = ft_strjoin(aux->file, ".heredoc");
				unlink(aux_char);
				free(aux_char);
				aux_char = NULL;
			}
			aux = aux->next;
		}
		aux_cmd = aux_cmd->next;
	}
	return (0);
}
