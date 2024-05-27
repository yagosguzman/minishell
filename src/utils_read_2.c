/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_read_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 22:51:20 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/13 21:20:05 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	insert_env(t_comand *cmds, t_env **env_list)
{
	cmds->env = env_list;
	cmds->envp = env_executor(env_list);
}

void	count_word_loop(char *line, int *i, int *first_pos)
{
	while (line[*i] != '\0' && line[*i] != ' ' && line[*i] != '|')
	{
		if ((line[*i] == '<' || line[*i] == '>'))
		{
			if (*i == *first_pos)
			{
				check_redir(line, i);
				continue ;
			}
			else
				break ;
		}
		if (line[*i] == 34 || line[*i] == 39)
			check_quote(line, i);
		else
			(*i)++;
	}
}

void	util_count_word(char *line, int *i)
{
	int	first_pos;

	while (line[*i] != '\0' && line[*i] == ' ')
		(*i)++;
	first_pos = *i;
	count_word_loop(line, i, &first_pos);
	if (line[*i] == '|' && *i == first_pos)
		(*i)++;
	while (line[*i] != '\0' && line[*i] == ' ')
		(*i)++;
}

int	count_word(char *line)
{
	int		words;
	int		i;

	i = 0;
	words = 0;
	while (line[i] != '\0')
	{
		util_count_word(line, &i);
		words++;
	}
	return (words);
}
