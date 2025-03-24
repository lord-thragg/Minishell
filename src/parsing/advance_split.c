/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:32:14 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/24 10:13:17 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*res;

	res = malloc(n + 1);
	if (!res)
		return (NULL);
	memcpy(res, s, n);
	res[n] = '\0';
	return (res);
}

size_t	count_quotes(const char *s, size_t *i, char quote)
{
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] == quote)
		(*i)++;
	return (1);
}

size_t	count_segments(const char *s, size_t *i)
{
	size_t	segnum;

	segnum = 0;
	while (s[*i])
	{
		while (s[*i] == ' ' || s[*i] == '\t')
			(*i)++;
		if (!s[*i])
			break ;
		if (s[*i] == '\'' || s[*i] == '"')
			segnum += count_quotes(s, i, s[*i]);
		else if (s[*i] == '|')
		{
			segnum++;
			(*i)++;
		}
		else
		{
			while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '\''
				&& s[*i] != '"' && s[*i] != '|')
				(*i)++;
			segnum++;
		}
	}
	return (segnum);
}

size_t	segcount(const char *s)
{
	size_t	i;

	i = 0;
	return (count_segments(s, &i));
}
