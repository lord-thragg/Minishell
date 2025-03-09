/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:39:35 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/08 10:52:17 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	segcount(char const *s, char c)
{
	size_t	i;
	size_t	segnum;
	int		in_quote;

	i = 0;
	segnum = 0;
	in_quote = 0;
	while (s[i])
	{
		while (s[i] == c && !in_quote)
			i++;
		if (s[i])
			segnum++;
		while ((s[i] && s[i] != c) || (in_quote && i < ft_strlen(s)))
		{
			if (s[i] == '"' || s[i] == '\'')
				in_quote = !in_quote;
			i++;
		}
	}
	return (segnum);
}

static char	*copy_without_quotes(const char *s, size_t start, size_t end)
{
	size_t	len;
	char	*result;
	size_t	j;

	len = end - start;
	result = (char *)malloc(len + 1);
	j = 0;
	if (!result)
		return (NULL);
	while (start < end)
	{
		if (s[start] != '"' && s[start] != '\'')
			result[j++] = s[start];
		start++;
	}
	result[j] = '\0';
	return (result);
}

static char	**spliter(char **split, char const *s, char c, size_t start)
{
	size_t	i;
	size_t	j;
	int		in_quote;

	i = 0;
	j = 0;
	in_quote = 0;
	while (s[i])
	{
		i = advance_to_next_segment(s, c, i, &in_quote);
		start = i;
		i = advance_through_segment(s, c, i, &in_quote);
		if (i > start)
		{
			split[j] = copy_without_quotes(s, start, i);
			if (!split[j])
				return (fsplit(split, j), NULL);
			j++;
		}
	}
	return (split[j] = NULL, split);
}

char	**ft_splitspace(char const *s)
{
	size_t	segnum;
	char	**splited;

	if (!s)
		return (NULL);
	segnum = segcount(s, ' ');
	splited = (char **)malloc((segnum + 1) * sizeof(char *));
	if (!splited)
		return (NULL);
	if (!spliter(splited, s, ' ', 0))
		return (NULL);
	return (splited);
}
