/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 23:13:53 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/09 23:06:02 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	aux_leng_word(char *line, int *leng, int *space)
{
	while (line[*leng] != '\0' && line[*leng] != ' ')
	{
		if (line[*leng] == 34 || line[*leng] == 39)
		{
			check_quote(line, &(*leng));
			break ;
		}
		if ((line[*leng] == '<' || line[*leng] == '>') && *leng == 0)
		{
			(*space) += check_redir(line, &(*leng));
			continue ;
		}
		if (*leng > 0 && (line[*leng] == '<' || line[*leng] == '>'))
			break ;
		if (line[*leng] == '|')
		{
			if (*leng == 0)
				(*leng)++;
			break ;
		}
		(*leng)++;
	}
}

int	leng_word(char *line)
{
	int		leng;
	int		space;

	leng = 0;
	space = 0;
	aux_leng_word(line, &leng, &space);
	return (leng - space);
}

int	copy_word(char *dest, char *src, int *j)
{
	int		i;

	i = 0;
	while (src[*j] != '\0' && src[*j] != ' ')
	{
		if (src[*j] == 34 || src[*j] == 39)
			return (copy_quote(src, &dest[i], j));
		if (i == 0 && (src[*j] == '<' || src[*j] == '>'))
			return (copy_redir(src, dest, j));
		if ((src[*j] == '<' || src[*j] == '>'))
			break ;
		if (src[*j] == '|')
		{
			if (i == 0)
				dest[i++] = src[(*j)++];
			break ;
		}
		dest[i++] = src[(*j)++];
	}
	dest[i] = '\0';
	return (0);
}
