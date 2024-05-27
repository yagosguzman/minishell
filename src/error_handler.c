/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 18:13:15 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/06 16:13:23 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_error(char *errmsg, int error)
{
	g_status = error;
	while (*errmsg)
		write(STDERR_FILENO, errmsg++, 1);
	return (g_status);
}

void	ft_closefd(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	exit_error(char *str)
{
	printf("%s\n", str);
	exit(g_status);
}

int	magic_ft_error(char *cmd, char *arg, char *errmsg, int error)
{
	g_status = error;
	if (cmd != NULL)
	{
		while (*cmd)
			write(STDERR_FILENO, cmd++, 1);
		write(STDERR_FILENO, ": ", 2);
	}
	if (arg != NULL)
	{
		write(STDERR_FILENO, "`", 1);
		while (*arg)
			write(STDERR_FILENO, arg++, 1);
		write(STDERR_FILENO, "': ", 3);
	}
	while (*errmsg)
		write(STDERR_FILENO, errmsg++, 1);
	return (g_status);
}
