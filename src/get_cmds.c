/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:14:49 by gpinilla          #+#    #+#             */
/*   Updated: 2024/03/28 20:33:33 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_flag_redir(char *word, t_comand **cmds)
{
	int		i;
	int		j;
	t_inout	*redir;

	i = 0;
	j = -1;
	redir = init_inout(cmds);
	if (word[0] == '<' && word[1] != '<')
		redir->type = IN;
	else if (word[0] == '>' && word[1] != '>')
		redir->type = OUT;
	else if (word[0] == '<' && word[1] == '<')
		redir->type = HEREDOC;
	else if (word[0] == '>' && word[1] == '>')
		redir->type = APPEND;
	i = (redir->type / 3) + 1;
	redir->file = malloc(sizeof(char) * ft_strlen(&word[i]) + 1);
	if (!redir->file)
		return (-1);
	while (word[i + (++j)])
		redir->file[j] = word[i + j];
	redir->file[j] = '\0';
	return (0);
}

t_comand	*get_flag_pipe(t_comand **cmds, int *i, int *n_args)
{
	t_comand	*aux;

	*n_args = 0;
	aux = newcmd(*cmds);
	aux->pipe_line = (*cmds)->pipe_line + 1;
	aux->env = (*cmds)->env;
	(*i)++;
	return (aux);
}

int	get_args(char **words, t_comand *cmds, int *i, int *n_args)
{
	int	j;

	j = 0;
	cmds->arg[*n_args] = ft_calloc(sizeof (char), (ft_strlen(words[*i]) + 1));
	if (!cmds->arg[*n_args])
		return (-1);
	while (words[*i][j])
	{
		cmds->arg[*n_args][j] = words[*i][j];
		j++;
	}
	cmds->arg[*n_args][j] = '\0';
	(*i)++;
	(*n_args)++;
	return (0);
}
