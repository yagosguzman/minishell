/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 16:37:52 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/19 22:00:42 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	count_args(char **words, t_comand *cmd)
{
	int	i;

	i = 0;
	while (words[i] != NULL && words[i][0] != '|')
	{
		if (words[i][0] != '<' && words[i][0] != '>')
			cmd->num_arg++;
		i++;
	}
}

void	get_flags(char **words, t_comand **cmds, int *i, int *n_args)
{
	if (words[*i][0] == '<' || words[*i][0] == '>')
		get_flag_redir(words[(*i)++], cmds);
	else if (words[*i][0] == '|')
	{
		*cmds = get_flag_pipe(cmds, i, n_args);
		count_args(&words[*i], *cmds);
		(*cmds)->arg = ft_calloc(sizeof(char *), ((*cmds)->num_arg + 1));
		if (!((*cmds)->arg))
			ft_error("error malloc\n", 1);
	}
}

void	get_tokens(char **words, t_comand **cmds)
{
	int		i;
	int		n_args;

	i = 0;
	n_args = 0;
	while (words[i])
	{
		if (words[i][0] == '<' || words[i][0] == '>'
			|| words[i][0] == '|')
			get_flags(words, cmds, &i, &n_args);
		else
			get_args(words, *cmds, &i, &n_args);
	}
}

void	get_words(char *line, t_comand **cmds)
{
	char	**words;
	int		i;
	int		j;

	i = 0;
	j = 0;
	words = (char **)ft_calloc(sizeof(char *), (count_word(line) + 1));
	if (!words)
		ft_error("error\n", 1);
	while (line[j] != '\0')
	{
		while (line[j] != '\0' && line[j] == ' ')
			j++;
		words[i] = (char *)ft_calloc(sizeof(char), leng_word(&line[j]) + 1);
		if (!words[i])
			ft_error("error\n", 1);
		copy_word(words[i++], line, &j);
		while (line[j] != '\0' && line[j] == ' ')
			j++;
	}
	words[i] = NULL;
	count_args(words, *cmds);
	(*cmds)->arg = (char **)ft_calloc(sizeof(char *), ((*cmds)->num_arg + 1));
	get_tokens(words, cmds);
	free_words(&words);
}

t_comand	*get_line(t_env **env_list)
{
	char		*line;
	t_comand	*cmds;
	t_comand	*list;

	cmds = NULL;
	list = NULL;
	line = readline("Minishell> ");
	if (line == NULL && cmds == NULL)
		safe_exit(&env_list);
	if (check_only_space(line) != -1 || line[0] != '\0')
	{
		cmds = create_cmd();
		list = cmds;
		insert_env(cmds, env_list);
		add_history(line);
		get_words(line, &cmds);
	}
	if (cmds != NULL && check_errors(list) != 1)
	{
		free_cmds(&list);
	}
	free(line);
	return (list);
}
