/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 18:35:04 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/06 16:26:08 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_wordlen(char *s, char c)
{
	int	len;

	len = 0;
	while (*s && *s++ != c)
		len++;
	return (len);
}

char	*ft_strndup(char *env_value, char *cmd, char c)
{
	int		len;
	char	*path;
	int		i;

	i = 0;
	len = ft_wordlen(env_value, c);
	path = (char *)malloc(sizeof(char) * (len + ft_strlen(cmd) + 2));
	if (!path)
		return (NULL);
	while (i < len)
	{
		path[i] = env_value[i];
		i++;
	}
	path[i++] = '/';
	while (*cmd != '\0')
		path[i++] = *(cmd++);
	path[i] = '\0';
	return (path);
}

int	split_count_words(char *env_value, char c)
{
	int	count;

	count = 0;
	while (*env_value && *env_value == c)
		env_value++;
	while (*env_value)
	{
		count++;
		while (*env_value && *env_value != c)
			env_value++;
		while (*env_value && *env_value == c)
			env_value++;
	}
	return (count);
}

int	ft_free_arr(char **s, int i)
{
	while (i >= 0)
		free(s[i--]);
	free(s);
	return (0);
}

void	ft_tolower_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = ft_tolower(str[i]);
		i++;
	}
}
