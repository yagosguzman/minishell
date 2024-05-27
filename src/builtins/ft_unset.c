/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 16:52:56 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/17 21:24:55 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_env	*free_env(t_env **env)
{
	free(env[0]->name);
	if (env[0]->value != NULL)
		free(env[0]->value);
	env[0]->prev = NULL;
	env[0]->next = NULL;
	free(env[0]);
	env[0] = NULL;
	env = NULL;
	return (NULL);
}

static t_env	*delete_first_node(t_env **env)
{
	t_env	*aux;

	aux = env[0]->next;
	env[0]->next->prev = NULL;
	free_env(env);
	return (aux);
}

static t_env	*delete_last_node(t_env **env)
{
	t_env	*aux;

	aux = env[0]->prev;
	env[0]->prev->next = NULL;
	free_env(env);
	return (aux);
}

int	delete_env_var(t_env **env)
{
	t_env	*aux;

	if (!env[0]->prev && !env[0]->next)
		free_env(env);
	else if (!env[0]->prev)
		env[0] = delete_first_node(env);
	else if (!env[0]->next)
		env[0] = delete_last_node(env);
	else
	{
		aux = env[0]->prev;
		env[0]->prev->next = env[0]->next;
		env[0]->next->prev = env[0]->prev;
		free_env(env);
		env[0] = aux;
	}
	return (0);
}

int	ft_unset(t_comand *cmd, int argc, char **argv)
{
	int		i;

	if (!cmd->env[0] || argc < 2)
		return (0);
	i = 1;
	while (i < cmd->num_arg)
	{
		while (cmd->env[0])
		{
			if (!ft_strncmp(cmd->env[0]->name, argv[i], ft_strlen(argv[i]) + 1))
			{
				delete_env_var(cmd->env);
				break ;
			}
			if (cmd->env[0]->next == NULL)
				break ;
			cmd->env[0] = cmd->env[0]->next;
		}
		while (cmd->env[0] && cmd->env[0]->prev != NULL)
			cmd->env[0] = cmd->env[0]->prev;
		i++;
	}
	return (0);
}
