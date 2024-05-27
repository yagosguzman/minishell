/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 17:28:47 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/21 17:57:40 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	magic_atoi(char *nbr)
{
	int	result;

	result = ft_atoi(nbr);
	if (result < 0)
		while (result < 0)
			result += 256;
	else
	{
		while (result > 255)
			result -= 256;
	}
	return (result);
}

t_env	*create_new_env(t_comand *cmd, char **argv, int i)
{
	t_env	*new_env;

	if (!cmd->env[0])
	{
		cmd->env[0] = create_first_node(argv[i]);
		return (cmd->env[0]);
	}
	new_env = cmd->env[0];
	while (new_env->next)
		new_env = new_env->next;
	new_env->next = (t_env *)ft_calloc(sizeof(t_env), 1);
	if (!new_env->next)
		return (free_env_list(new_env));
	new_env->next->prev = new_env;
	new_env = new_env->next;
	new_env->name = get_pre_char(argv[i], '=');
	if (new_env->name == NULL)
	{
		new_env->prev->next = NULL;
		return (free_env(&new_env));
	}
	new_env->value = get_post_char(argv[i], '=');
	return (new_env);
}

int	cd_nodir(char *argv)
{
	char		*curr_dir;
	struct stat	*stat_s;

	stat_s = malloc(sizeof(struct stat));
	if (!stat_s)
		return (ft_error("ft_cd: problem creating malloc\n", 1));
	curr_dir = ft_strdup(argv);
	if (stat(curr_dir, stat_s) == 0)
	{
		if (!S_ISDIR(stat_s->st_mode))
		{
			free(stat_s);
			free(curr_dir);
			return (ft_error("Not a directory\n", 1));
		}
		free(stat_s);
		if (chdir(curr_dir) == -1)
		{
			free(curr_dir);
			return (1);
		}
	}
	free(curr_dir);
	return (0);
}

void	no_cwd(t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux && ft_strncmp(aux->name, "PWD", ft_strlen("PWD") + 1) != 0)
		aux = aux->next;
	if (aux)
		cd_nodir(aux->value);
}
