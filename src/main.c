/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 19:24:22 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/23 18:41:38 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	minishell_loop(t_env **env_list)
{
	t_comand	*cmds;
	t_comand	*list;
	t_pipe		*pipe_s;

	pipe_s = NULL;
	while (1)
	{
		wait_signal(1);
		cmds = get_line(env_list);
		list = cmds;
		if (cmds == NULL)
			continue ;
		expander(cmds);
		cmds = list;
		pipe_s = init_pipe_s(cmds);
		executor(cmds, pipe_s);
		if (pipe_s)
			free_pipe_s(&pipe_s);
		if (cmds)
			free_cmds(&cmds);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env		**env_list;

	if (argc >= 1 && argv[0])
	{
		env_list = (t_env **)malloc(sizeof(t_env *));
		if (!env_list)
			return (ft_error("malloc error\n", 1));
		if (envp && !(*envp))
			env_list[0] = minimum_env();
		else
			env_list[0] = create_env_list(envp);
		minishell_loop(env_list);
	}
	return (0);
}
