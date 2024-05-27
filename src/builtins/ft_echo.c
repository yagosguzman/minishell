/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 15:41:52 by ysanchez          #+#    #+#             */
/*   Updated: 2024/04/15 20:20:13 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_check_n(char **argv, int *i)
{
	int	j;

	j = 2;
	while (argv[*i] && !ft_strncmp ("-n", argv[*i], ft_strlen("-n")))
	{
		while (argv[*i][j] == 'n' && argv[*i][j] != '\0')
			j++;
		if (argv[*i][j] != '\0')
			break ;
		(*i)++;
		j = 2;
	}
	if (*i == 1)
		return (0);
	else
		return (1);
}

int	ft_echo(int argc, char **argv)
{
	int	i;
	int	space_flag;

	i = 1;
	space_flag = 0;
	if (argc == 1)
		ft_printf("\n");
	else
	{
		if ((argc >= 1) && (!ft_strncmp ("-n", argv[1], ft_strlen("-n"))))
			space_flag = ft_check_n(argv, &i);
		if ((space_flag == 1 || i == 1) && i < argc)
			ft_printf("%s", argv[i++]);
		while (i < argc)
		{
			ft_printf(" ");
			ft_printf("%s", argv[i]);
			i++;
		}
		if (space_flag == 0)
			ft_printf("\n");
	}
	return (0);
}
