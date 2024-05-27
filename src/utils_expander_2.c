/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_expander_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 21:29:51 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/13 21:36:51 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*expand_var(char *str, char *value, char *name, t_aux *s_aux)
{
	int		i;
	int		j;
	char	*aux;
	int		len;

	i = 0;
	j = 0;
	if (value)
		len = ft_strlen(str) - (ft_strlen(name) + 1) + ft_strlen(value) + 1;
	else
		len = ft_strlen(str) - ft_strlen(name) + 1;
	aux = ft_calloc(len, sizeof(char));
	if (!aux)
		return (NULL);
	while (str[i] != '$')
		aux[j++] = str[i++];
	i += ft_strlen(name) + 1;
	if (value != NULL)
		while (*value)
			aux[j++] = *(value++);
	reset_malloc(s_aux, len);
	while (str[i])
		aux[j++] = str[i++];
	free(str);
	return (aux);
}

int	search_env_var(char **argv, t_aux *aux, t_env *env, int i)
{
	t_env	*iter_env;

	iter_env = env;
	if (aux->name[0] != '\0')
	{
		while (iter_env)
		{
			if (ft_strncmp(iter_env->name, aux->name, (aux->k + 1)) == 0)
			{
				argv[i] = expand_var(argv[i], iter_env->value, aux->name, aux);
				if (!argv[i])
					return (ft_error("Problem with malloc in expander\n", 1));
				return (0);
			}
			else
				iter_env = iter_env->next;
		}
		argv[i] = expand_var(argv[i], NULL, aux->name, aux);
		if (!argv[i])
			return (ft_error("Problem with malloc in expander\n", 1));
		return (0);
	}
	return (0);
}

void	save_and_expand(t_comand *cmd, int i, t_aux *aux)
{
	aux->expand = &cmd->arg[i][aux->j++];
	if (check_special_cases(cmd, i, cmd->arg[i][aux->j], aux))
		while (valid_name(cmd->arg[i][aux->j]) == 0)
			aux->name[aux->k++] = cmd->arg[i][aux->j++];
	search_env_var(cmd->arg, aux, cmd->env[0], i);
}
