/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/13 19:30:01 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/21 17:53:19 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	change_pwd(t_env *env, char *oldpwd)
{
	t_env	*iter_env;

	iter_env = env;
	while (iter_env && ft_strncmp(iter_env->name, "OLDPWD", 7))
		iter_env = iter_env->next;
	if (iter_env && !ft_strncmp(iter_env->name, "OLDPWD", 7)
		&& (ft_strlen(iter_env->name) == ft_strlen("OLDPWD")))
		change_value(ft_strdup(oldpwd), iter_env);
	iter_env = env;
	while (iter_env && ft_strncmp(iter_env->name, "PWD", 4))
		iter_env = iter_env->next;
	if (iter_env && !ft_strncmp(iter_env->name, "PWD", 4)
		&& (ft_strlen(iter_env->name) == ft_strlen("PWD")))
		change_value(getcwd(NULL, sizeof(char)), iter_env);
}

int	aux_stat_ok(struct stat *stat_s, char *curr_dir)
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
		ft_error(curr_dir, 1);
		free(curr_dir);
		return (ft_error("/: Permission denied\n", 1));
	}
	return (0);
}

int	cd_2arg(char **argv)
{
	char		*curr_dir;
	struct stat	*stat_s;

	stat_s = malloc(sizeof(struct stat));
	if (!stat_s)
		return (ft_error("ft_cd: problem creating malloc\n", 1));
	curr_dir = ft_strdup(argv[1]);
	if (stat(curr_dir, stat_s) < 0)
	{
		free(curr_dir);
		free(stat_s);
		return (ft_error("No such file or directory\n", 1));
	}
	if (stat(curr_dir, stat_s) == 0)
		aux_stat_ok(stat_s, curr_dir);
	free(curr_dir);
	return (0);
}

int	cd_home(char *oldpwd)
{
	if (chdir(getenv("HOME")) == -1)
	{
		free(oldpwd);
		return (1);
	}
	return (0);
}

int	ft_cd(int argc, char **argv, t_env *env)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, sizeof(oldpwd));
	if (oldpwd == NULL)
		no_cwd(env);
	if (argc == 1 || (argc == 2 && argv[1][0] == '~'
		&& ft_strlen(argv[1]) == 1))
		cd_home(oldpwd);
	else if (argc > 1)
	{
		if (cd_2arg(argv) != 0)
		{
			free(oldpwd);
			return (1);
		}
	}
	change_pwd (env, oldpwd);
	free(oldpwd);
	return (0);
}
