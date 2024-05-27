/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor_checks.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 16:22:35 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/19 20:23:16 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_builtin(char *command)
{
	char	*aux;
	int		func;

	func = -1;
	aux = ft_strdup(command);
	ft_tolower_str(aux);
	if (ft_strncmp("echo", aux, (ft_strlen("echo") + 1)) == 0)
		func = 0;
	else if (ft_strncmp("cd", aux, (ft_strlen("cd") + 1)) == 0)
		func = 1;
	else if (ft_strncmp("pwd", aux, (ft_strlen("pwd") + 1)) == 0)
		func = 2;
	else if (ft_strncmp("export", aux, (ft_strlen("export") + 1)) == 0)
		func = 3;
	else if (ft_strncmp("unset", aux, (ft_strlen("unset") + 1)) == 0)
		func = 4;
	else if (ft_strncmp("env", aux, (ft_strlen("env") + 1)) == 0)
		func = 5;
	else if (ft_strncmp("exit", aux, (ft_strlen("exit") + 1)) == 0)
		func = 6;
	free(aux);
	return (func);
}

int	exec_builtin(t_comand *cmd, int result, t_pipe *pipe_s)
{
	if (result == 0)
		g_status = ft_echo(cmd->num_arg, cmd->arg);
	else if (result == 1)
		g_status = ft_cd(cmd->num_arg, cmd->arg, cmd->env[0]);
	else if (result == 2)
		g_status = ft_pwd(cmd->env[0]);
	else if (result == 3)
		g_status = ft_export(cmd, cmd->num_arg, cmd->arg);
	else if (result == 4)
		g_status = ft_unset(cmd, cmd->num_arg, cmd->arg);
	else if (result == 5)
		g_status = ft_env(cmd->num_arg, cmd->env[0]);
	else if (result == 6)
		g_status = ft_exit(&cmd, &pipe_s);
	else
		g_status = 1;
	return (g_status);
}

char	*check_cmds(char **split, char *arg)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (split[i] && access(split[i], F_OK) != 0)
		i++;
	if (!split[i])
	{
		ft_error(arg, 127);
		ft_error(": command not found\n", 127);
		return (NULL);
	}
	if (access(split[i], X_OK) != 0)
	{
		ft_error(arg, 126);
		ft_error(": Permission denied\n", 126);
		return (NULL);
	}
	cmd_path = ft_strdup(split[i]);
	return (cmd_path);
}

char	**magic_split(char *env_value, char c, char *cmd)
{
	char	**split;
	int		count;
	int		i;

	i = 0;
	if (cmd[i] == '.')
		return (NULL);
	count = split_count_words(env_value, c);
	split = (char **)ft_calloc(sizeof(char *), (count + 1));
	if (!split)
		return (NULL);
	while (i < count)
	{
		while (*env_value && *env_value == c)
			env_value++;
		split[i] = ft_strndup(env_value, cmd, c);
		if (!split[i])
		{
			ft_free_arr(split, i - 1);
			return (split);
		}
		env_value += ft_wordlen(env_value, c);
		i++;
	}
	return (split);
}

char	*path_searcher(t_comand *cmd)
{
	t_env	*iter_env;
	char	**split_path;
	char	*cmd_path;

	split_path = NULL;
	cmd_path = NULL;
	iter_env = cmd->env[0];
	split_path = path_searcher_loop(split_path, iter_env, cmd);
	if (split_path != NULL)
	{
		cmd_path = check_cmds(split_path, cmd->arg[0]);
		free_words(&split_path);
	}
	else if (cmd_path == NULL)
	{
		ft_error(cmd->arg[0], 127);
		if (is_file_dir(cmd->arg[0]))
			ft_error(": No such file or directory\n", 127);
		else
			ft_error(": command not found\n", 127);
	}
	return (cmd_path);
}
