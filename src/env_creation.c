/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 18:26:42 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/19 21:10:37 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*free_env_list(t_env *env)
{
	if (env)
	{
		if (env->name)
			free(env->name);
		if (env->value)
			free(env->value);
		if (env->next)
			free_env_list(env->next);
		free(env);
	}
	return (NULL);
}

t_env	*create_min_node(char *name, char *value, t_env *env)
{
	t_env	*new_node;

	new_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_node)
		return (NULL);
	env->next = new_node;
	new_node->prev = env;
	new_node->name = ft_strdup(name);
	if (!new_node->name)
		return (NULL);
	if (value != NULL)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
			return (NULL);
	}
	return (new_node);
}

t_env	*minimum_env(void)
{
	t_env	*env_min;
	t_env	*env_iter;

	env_min = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!env_min)
		return (NULL);
	env_iter = env_min;
	env_iter->name = ft_strdup("PWD");
	if (!env_iter->name)
		return (NULL);
	env_iter->value = getcwd(NULL, sizeof(char *));
	env_iter->next = create_min_node("SHLVL", "1", env_iter);
	if (!env_iter->next)
		return (free_env_list(env_min));
	env_iter = env_iter->next;
	env_iter->next = create_min_node("OLDPWD", NULL, env_iter);
	if (!env_iter->next)
		return (free_env_list(env_min));
	env_iter = env_iter->next;
	return (env_min);
}

t_env	*create_env_list(char **env)
{
	t_env	*env_struct;
	t_env	*env_iter;
	int		i;

	i = 0;
	env_struct = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!env_struct)
		return (NULL);
	env_iter = env_struct;
	env_iter->name = get_pre_char(env[i], '=');
	env_iter->value = get_post_char(env[i], '=');
	while (env[++i])
	{
		env_iter->next = (t_env *)ft_calloc(sizeof(t_env), 1);
		if (!env_iter->next)
			return (free_env_list(env_struct));
		env_iter->next->prev = env_iter;
		env_iter = env_iter->next;
		env_iter->name = get_pre_char(env[i], '=');
		if (!env_iter->name)
			return (free_env_list(env_struct));
		if (!shlvl_increaser(env_iter, env, &i))
			env_iter->value = get_post_char(env[i], '=');
	}
	return (env_struct);
}

t_env	*create_first_node(char *arg)
{
	t_env	*first_node;

	first_node = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!first_node)
		return (NULL);
	first_node->name = get_pre_char(arg, '=');
	if (!first_node->name)
		return (free_env_list(first_node));
	first_node->value = get_post_char(arg, '=');
	return (first_node);
}
