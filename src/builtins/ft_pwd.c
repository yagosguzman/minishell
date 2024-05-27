/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:43:18 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/17 15:57:56 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_env *env)
{
	char	*dir;
	t_env	*aux;

	dir = getcwd(NULL, sizeof(dir));
	if (dir == NULL)
	{
		aux = env;
		while (aux && ft_strncmp(aux->name, "PWD", ft_strlen("PWD") + 1) != 0)
			aux = aux->next;
		if (aux)
			dir = ft_strdup(aux->value);
	}
	printf("%s\n", dir);
	free(dir);
	return (0);
}
