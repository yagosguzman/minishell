/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_checks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 18:31:22 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/10 19:58:38 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_empty_redir(t_comand *cmd)
{
	t_inout	*aux;

	while (cmd)
	{
		aux = cmd->redir;
		while (aux)
		{
			if (aux->file[0] == '\0')
			{
				ft_error("syntax error near unexpected token `|'\n", 258);
				return (-1);
			}
			aux = aux->next;
		}
		cmd = cmd->next;
	}
	return (1);
}

int	check_empty_pipes(t_comand *cmd)
{
	while (cmd)
	{
		if (cmd->arg[0] == NULL)
		{
			ft_error("syntax error near unexpected token `|'\n", 258);
			return (-1);
		}
		cmd = cmd->next;
	}
	return (1);
}

int	check_only_space(char *s)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (s && s[++i])
	{
		if (s[i] == '\t' || s[i] == '\n'
			|| s[i] == '\v' || s[i] == '\f'
			|| s[i] == '\r' || s[i] == ' ')
			j++;
	}
	if (j == i)
		return (-1);
	return (0);
}

int	check_errors(t_comand *cmd)
{
	int	error;

	error = 1;
	if (error == 1)
		error = check_empty_pipes(cmd);
	if (error == 1)
		error = check_empty_redir(cmd);
	return (error);
}
