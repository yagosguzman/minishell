/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysanchez <ysanchez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 22:27:29 by gpinilla          #+#    #+#             */
/*   Updated: 2024/04/08 21:05:33 by ysanchez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_quote(char *line, int *leng)
{
	int	quote;

	quote = line[(*leng)++];
	while (((line[*leng] != ' ' && line[*leng] != '>' && line[*leng] != '<'
				&& line[*leng] != '|') || quote != 0) && line[*leng])
	{
		if (quote == 0 && (line[*leng] == 34 || line[*leng] == 39))
			quote = line[*leng];
		else if (quote == line[*leng])
			quote = 0;
		(*leng)++;
	}
	return (quote);
}

int	check_redir(char *line, int *leng)
{
	int	space;

	space = 0;
	if ((line[*leng] == '<' && line[*leng + 1] == '<')
		|| (line[*leng] == '>' && line[*leng + 1] == '>'))
		*leng += 2;
	else
		(*leng)++;
	while (line[*leng] == ' ')
	{
		(*leng)++;
		space++;
	}
	return (space);
}

int	copy_quote(char *src, char *dest, int *i)
{
	int	quote;
	int	j;

	j = 0;
	quote = src[*i];
	dest[j++] = src[(*i)++];
	while (src[*i] != '\0' && ((src[(*i)] != ' ' && src[(*i)] != '>'
				&& src[(*i)] != '<' && src[(*i)] != '|') || quote != 0))
	{
		if (quote == 0 && (src[*i] == 34 || src[*i] == 39))
			quote = src[*i];
		else if (quote == src[*i])
			quote = 0;
		dest[j++] = src[(*i)++];
	}
	dest[j] = '\0';
	return (quote);
}

int	copy_quote_redir(char *src, char *dest, int *i, int *j)
{
	int	quote;

	quote = src[*i];
	dest[(*j)++] = src[(*i)++];
	while (src[*i] != '\0' && ((src[(*i)] != ' ' && src[(*i)] != '>'
				&& src[(*i)] != '<' && src[(*i)] != '|') || quote != 0))
	{
		if (quote == 0 && (src[*i] == 34 || src[*i] == 39))
			quote = src[*i];
		else if (quote == src[*i])
			quote = 0;
		dest[(*j)++] = src[(*i)++];
	}
	dest[*j] = '\0';
	return (quote);
}

int	copy_redir(char *src, char *dest, int *i)
{
	int	j;

	j = 0;
	dest[j++] = src[(*i)++];
	if ((src[*i] == '<' && src[*i - 1] == '<')
		|| (src[*i] == '>' && src[*i - 1] == '>'))
		dest[j++] = src[(*i)++];
	while (src[*i] == ' ')
		(*i)++;
	while (src[*i] != ' ' && src[*i] != '<'
		&& src[*i] != '>' && src[*i] != '|' && src[*i] != '\0')
	{
		if (src[*i] == 34 || src[*i] == 39)
		{
			copy_quote_redir(src, dest, i, &j);
			break ;
		}
		dest[j++] = src[(*i)++];
	}
	dest[j] = '\0';
	return (*i);
}
