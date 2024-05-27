/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/24 18:04:28 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/17 19:47:09 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_aux	*init_aux_struct(t_comand *cmd, int i)
{
	t_aux	*aux;

	aux = NULL;
	aux = (t_aux *)ft_calloc(sizeof(t_aux), 1);
	if (!aux)
		return (NULL);
	aux->arg = ft_calloc((ft_strlen(cmd->arg[i]) + 1), sizeof(char));
	if (!aux->arg)
		return (free_aux_struc(&aux));
	aux->name = ft_calloc((ft_strlen(cmd->arg[i]) + 1), sizeof(char));
	if (!aux->name)
		return (free_aux_struc(&aux));
	return (aux);
}

int	reset_malloc(t_aux *aux, int malloc_len)
{
	if ((*aux->name) != '\0')
		free(aux->name);
	aux->name = ft_calloc(malloc_len, sizeof(char));
	if (!aux->name)
		return (ft_error("Problem with malloc (Reset expander)\n", 1));
	if ((*aux->arg) != '\0')
		free(aux->arg);
	aux->arg = ft_calloc(malloc_len, sizeof(char));
	if (!aux->arg)
		return (ft_error("Problem with malloc (Reset expander)\n", 1));
	aux->i = 0;
	aux->j = 0;
	aux->k = 0;
	aux->expand = NULL;
	return (0);
}

int	check_special_cases(t_comand *cmd, int i, char c, t_aux *aux)
{
	char	*pid;

	if (c == '?')
	{
		aux->name[0] = c;
		cmd->arg[i] = expand_var(cmd->arg[i],
				last_exit_status(), aux->name, aux);
		if (!cmd->arg[i])
			return (ft_error("Problem with malloc in expander\n", 1));
		return (0);
	}
	else if (c == '$')
	{
		pid = ft_itoa(getpid());
		aux->name[0] = c;
		cmd->arg[i] = expand_var(cmd->arg[i], pid, aux->name, aux);
		free(pid);
		if (!cmd->arg[i])
			return (ft_error("Problem with malloc in expander\n", 1));
		return (0);
	}
	else
		return (1);
}

void	swap_args(t_comand *cmd, int i, t_aux *aux)
{
	free(cmd->arg[i]);
	cmd->arg[i] = ft_strdup(aux->arg);
}
