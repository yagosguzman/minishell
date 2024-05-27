/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:20:07 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/19 21:43:23 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*last_exit_status(void)
{
	char	*exit_s;

	exit_s = ft_itoa(g_status);
	return (exit_s);
}

static void	checkers_exit(t_comand **cmd, int *i)
{
	while (ft_isspace(cmd[0]->arg[1][*i]))
		(*i)++;
	if ((cmd[0]->arg[1][*i] == '-' || cmd[0]->arg[1][*i] == '+'))
		(*i)++;
}

static void	aux_exit(t_comand **cmd, t_pipe **pipe_s)
{
	free_env_list(cmd[0]->env[0]);
	free(cmd[0]->env);
	if (pipe_s)
		free_pipe_s(pipe_s);
	free_cmds(cmd);
	exit(g_status);
}

int	ft_exit(t_comand **cmd, t_pipe **pipe_s)
{
	int	i;

	i = 0;
	rl_clear_history();
	if (cmd[0]->num_arg > 2)
		return (ft_error("exit: too many arguments\n", 1));
	else if (cmd[0]->num_arg == 2 && ft_strlen(cmd[0]->arg[1]) == 0)
		return (ft_error("exit:  : numeric argument required\n", 255));
	else if (cmd[0]->num_arg == 2)
	{
		checkers_exit(cmd, &i);
		if (cmd[0]->arg[1][i] == '\0')
			return (ft_error("exit:  : numeric argument required\n", 255));
		while (cmd[0]->arg[1][i] != '\0')
		{
			if (cmd[0]->arg[1][i] < '0' || cmd[0]->arg[1][i] > '9')
				return (ft_error("exit:  : numeric argument required\n", 255));
			i++;
		}
		g_status = magic_atoi(cmd[0]->arg[1]);
	}
	if (cmd[0]->num_arg == 2 || cmd[0]->num_arg == 1)
		aux_exit(cmd, pipe_s);
	return (g_status);
}
