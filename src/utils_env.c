/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 17:30:26 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/17 20:34:31 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	valid_name(char c)
{
	if ((c < 'a' || c > 'z') && (c < 'A' || c > 'Z')
		&& (c < '0' || c > '9') && (c != '_'))
		return (1);
	return (0);
}

char	*get_pre_char(char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	if (str[i] >= '0' && str[i] <= '9')
		return (NULL);
	while (str[i] && str[i] != c)
	{
		if (valid_name(str[i]) != 0)
			return (NULL);
		i++;
	}
	word = malloc(sizeof(char) * i + 1);
	if (!word)
		return (NULL);
	word[i] = '\0';
	while (i--)
		word[i] = str[i];
	return (word);
}

char	*get_post_char(char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (*str && *str != c)
		str++;
	if (*str != '\0')
		str++;
	else
		return (NULL);
	while (str[i])
		i++;
	word = malloc(sizeof(char) * i + 1);
	if (!word)
		return (NULL);
	word[i] = '\0';
	while (i--)
		word[i] = str[i];
	return (word);
}

int	shlvl_increaser(t_env *env_node, char **env, int *i)
{
	char	*shlvl;

	if (ft_strncmp(env_node->name, "SHLVL", ft_strlen("SHLVL") + 1) == 0)
	{
		shlvl = get_post_char(env[*i], '=');
		env_node->value = ft_itoa(ft_atoi(shlvl) + 1);
		free(shlvl);
		return (1);
	}
	return (0);
}

char	**env_executor(t_env **env)
{
	char	**envp;
	int		i;
	int		count;
	t_env	*aux;

	i = 0;
	aux = env[0];
	count = count_nodes(aux);
	envp = (char **)ft_calloc(sizeof(char *), count + 1);
	if (!envp)
		return (NULL);
	while (i < count)
	{
		envp[i] = magic_ft_strjoin(aux->name, aux->value, '=');
		i++;
		aux = aux->next;
	}
	envp[i] = NULL;
	return (envp);
}
