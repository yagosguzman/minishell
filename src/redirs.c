/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpinilla <gpinilla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 19:30:33 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/23 19:17:26 by gpinilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	set_redir(t_comand *cmd)
{
	t_inout	*aux;

	aux = cmd->redir;
	while (aux && g_status != 1)
	{
		if (aux->type == IN)
			g_status = ft_in(aux);
		else if (aux->type == OUT)
			g_status = ft_out(aux);
		else if (aux->type == HEREDOC)
			g_status = ft_heredoc(aux);
		else if (aux->type == APPEND)
			g_status = ft_append(aux);
		else
			return (ft_error("syntax error\n", 1));
		aux = aux->next;
	}
	return (g_status);
}

int	ft_in(t_inout *aux)
{
	int	fd;

	fd = open(aux->file, O_RDONLY);
	if (fd < 0)
		return (magic_ft_error(NULL, aux->file,
				"No such file or directory\n", 1));
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (g_status);
}

int	ft_out(t_inout *aux)
{
	int	fd;

	fd = open(aux->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		return (magic_ft_error(NULL, aux->file, "Permission denied\n", 1));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (g_status);
}

int	ft_heredoc(t_inout *aux)
{
	int		fd;
	char	*aux_char;

	aux_char = ft_strjoin(aux->file, ".heredoc");
	fd = open(aux_char, O_RDONLY);
	if (fd < 0)
		return (magic_ft_error(NULL, aux_char,
				"No such file or directory\n", 1));
	dup2(fd, STDIN_FILENO);
	close(fd);
	free(aux_char);
	return (g_status);
}

int	ft_append(t_inout *aux)
{
	int	fd;

	fd = open(aux->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		return (ft_error("open error\n", 1));
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (g_status);
}
