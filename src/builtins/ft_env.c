/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 16:33:16 by ysanchez          #+#    #+#             */
/*   Updated: 2024/03/30 12:19:51 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	print_env(t_env *env)
{
	t_env	*env_iter;

	env_iter = env;
	while (env_iter)
	{
		if (env_iter->name && env_iter->value)
			printf("%s=%s\n", env_iter->name, env_iter->value);
		env_iter = env_iter->next;
	}
	return (0);
}

int	ft_env(int argc, t_env *env)
{
	if (!env)
		return (1);
	if (argc == 1)
		return (print_env(env));
	return (0);
}
