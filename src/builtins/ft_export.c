/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:30:02 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/23 20:23:21 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	change_value(char *new, t_env *env_var)
{
	if (!new)
		return (0);
	free(env_var->value);
	env_var->value = new;
	return (0);
}

t_env	*print_export(t_env *iter_env)
{
	if (iter_env->value != NULL)
		printf("declare -x %s=\"%s\"\n", iter_env->name, iter_env->value);
	else
		printf("declare -x %s\n", iter_env->name);
	iter_env = iter_env->next;
	return (iter_env);
}

t_env	*check_if_exists(t_env *iter_env, char **argv, int i)
{
	char	*target;

	target = get_pre_char(argv[i], '=');
	while (iter_env)
	{
		if (target != NULL
			&& !ft_strncmp(iter_env->name, target, ft_strlen(target)))
		{
			change_value(get_post_char(argv[i], '='), iter_env);
			break ;
		}
		else
			iter_env = iter_env->next;
	}
	free(target);
	return (iter_env);
}

void	export_multiarg(t_comand *cmd, char **argv, int i, t_env *iter_env)
{
	while (i < cmd->num_arg)
	{
		iter_env = check_if_exists(iter_env, argv, i);
		if (iter_env == NULL)
		{
			iter_env = create_new_env(cmd, argv, i);
			if (iter_env == NULL)
				magic_ft_error(cmd->arg[0], cmd->arg[i],
					"not a valid identifier\n", 1);
		}
		iter_env = cmd->env[0];
		i++;
	}
}

int	ft_export(t_comand *cmd, int argc, char **argv)
{
	t_env	*iter_env;
	int		i;

	i = 1;
	iter_env = cmd->env[0];
	if (argc == 1)
	{
		if (!cmd->env[0])
			return (1);
		while (iter_env)
			iter_env = print_export(iter_env);
	}
	else
		export_multiarg(cmd, argv, i, iter_env);
	return (g_status);
}
