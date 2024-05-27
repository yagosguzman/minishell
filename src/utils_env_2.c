/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 21:24:09 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/13 21:25:03 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*magic_ft_strjoin(char const *s1, char const *s2, char c)
{
	size_t	len;
	int		i;
	char	*s;

	i = 0;
	if (s1 && s2)
		len = ft_strlen(s1) + ft_strlen(s2) + 2;
	else
		len = ft_strlen(s1) + 1;
	s = (char *)malloc((len) * sizeof(char));
	if (!s)
		return (0);
	while (*s1)
		s[i++] = *s1++;
	if (s2)
	{
		s[i++] = c;
		while (*s2)
			s[i++] = *s2++;
	}
	s[i] = '\0';
	return (s);
}

int	count_nodes(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}
