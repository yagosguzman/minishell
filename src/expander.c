/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:46:36 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/19 22:59:22 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	manage_single(t_aux *aux, char *str)
{
	while (str[aux->j] && str[aux->j] != '\'')
		aux->arg[aux->i++] = str[aux->j++];
}

void	manage_double(t_aux *aux, char *str, t_comand *cmd, int i)
{
	while (str[aux->j] && str[aux->j] != '\"')
	{
		if (str[aux->j] == '$' && str[aux->j + 1] && (str[aux->j + 1] == '$'
				|| str[aux->j + 1] == '?' || valid_name(str[aux->j + 1]) == 0))
		{
			save_and_expand(cmd, i, aux);
			break ;
		}
		else
			aux->arg[aux->i++] = str[aux->j++];
	}
}

void	manager_expander(t_comand *cmd, t_aux *aux, int *i)
{
	while (cmd->arg[*i][aux->j])
	{
		if (cmd->arg[*i][aux->j] == '$' && cmd->arg[*i][aux->j + 1] \
		&& (cmd->arg[*i][aux->j + 1] == '$' || cmd->arg[*i][aux->j + 1] == '?'
			|| valid_name(cmd->arg[*i][aux->j + 1]) == 0))
		{
			save_and_expand(cmd, *i, aux);
			continue ;
		}
		if (cmd->arg[*i][aux->j] == '\'' || cmd->arg[*i][aux->j] == '\"')
		{
			aux->j++;
			if (cmd->arg[*i][aux->j - 1] == '\'')
				manage_single(aux, cmd->arg[*i]);
			else if (cmd->arg[*i][aux->j - 1] == '\"')
				manage_double(aux, cmd->arg[*i], cmd, *i);
			else if (cmd->arg[*i][aux->j] != '\0')
				aux->j++;
		}
		else
			aux->arg[aux->i++] = cmd->arg[*i][aux->j++];
	}
}

void	max_expander(t_comand *cmd, int len)
{
	int		i;
	t_aux	*aux;

	aux = NULL;
	i = 0;
	while (i < len)
	{
		aux = init_aux_struct(cmd, i);
		manager_expander(cmd, aux, &i);
		swap_args(cmd, i, aux);
		free_aux_struc(&aux);
		i++;
	}
}

int	expander(t_comand *cmd)
{
	if (!cmd->arg || cmd->num_arg == 0)
		return (1);
	while (cmd != NULL)
	{
		max_expander(cmd, cmd->num_arg);
		cmd = cmd->next;
	}
	return (0);
}
