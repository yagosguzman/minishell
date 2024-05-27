/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_heredoc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 18:41:24 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/23 19:04:20 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_heredoc(t_comand *cmd, t_pipe *pipe_s)
{
	t_inout	*aux;

	aux = cmd->redir;
	while (aux && g_status != 1)
	{
		if (aux->type == HEREDOC)
			g_status = create_heredoc(aux, pipe_s);
		aux = aux->next;
	}
	return (g_status);
}

int	create_heredoc(t_inout *aux, t_pipe *pipe_s)
{
	int		fd;
	char	*line;
	char	*aux_char;

	aux_char = ft_strjoin(aux->file, ".heredoc");
	dup2((*pipe_s).og_fd[0], STDIN_FILENO);
	line = readline("> ");
	fd = open(aux_char, O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd < 0)
		return (ft_error("open error\n", 1));
	while (line && ft_strncmp(line, aux->file, ft_strlen(aux->file) + 1) != 0)
	{
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free (line);
		line = readline("> ");
	}
	free(aux_char);
	free(line);
	close(fd);
	return (g_status);
}
