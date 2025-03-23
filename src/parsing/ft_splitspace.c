/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:39:35 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/23 13:40:08 by luluzuri         ###   ########.fr       */
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

static void	skip_whitespace(const char *s, size_t *i)
{
	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
}

static size_t	count_quoted(const char *s, size_t *i)
{
	char	quote;

	quote = s[*i];
	(*i)++;
	while (s[*i] && s[*i] != quote)
		(*i)++;
	if (s[*i] == quote)
		(*i)++;
	return (1);
}

static size_t	count_token(const char *s, size_t *i)
{
	if (s[*i] == '|')
	{
		(*i)++;
		return (1);
	}
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && \
		s[*i] != '\'' && s[*i] != '"' && s[*i] != '|')
		(*i)++;
	return (1);
}

static size_t	segcount(const char *s)
{
	size_t	i;
	size_t	segnum;

	i = 0;
	segnum = 0;
	while (s[i])
	{
		skip_whitespace(s, &i);
		if (!s[i])
			break ;
		if (s[i] == '\'' || s[i] == '"')
			segnum += count_quoted(s, &i);
		else
			segnum += count_token(s, &i);
	}
	return (segnum);
}

static char	*process_single_quote(const char *s, size_t *i)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] == '\'')
		(*i)++;
	return (ft_strndup(s + start, *i - start));
}

static char	*process_double_quote(const char *s, size_t *i)
{
	size_t	start;
	char	*token;

	start = *i;
	(*i)++;
	while (s[*i] && s[*i] != '"')
		(*i)++;
	token = ft_strndup(s + start, *i - start);
	if (s[*i] == '"')
		(*i)++;
	return (token);
}

static char	*process_token(const char *s, size_t *i)
{
	size_t	start;

	start = *i;
	while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && \
		s[*i] != '\'' && s[*i] != '"' && s[*i] != '|')
		(*i)++;
	return (ft_strndup(s + start, *i - start));
}

static char	*process_pipe(size_t *i)
{
	(*i)++;
	return (ft_strndup("|", 1));
}

static char	**spliter(char **split, const char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
	{
		skip_whitespace(s, &i);
		if (!s[i])
			break ;
		if (s[i] == '\'' || s[i] == '"')
		{
			if (s[i] == '\'')
				split[j++] = process_single_quote(s, &i);
			else
				split[j++] = process_double_quote(s, &i);
		}
		else if (s[i] == '|')
			split[j++] = process_pipe(&i);
		else
			split[j++] = process_token(s, &i);
	}
	split[j] = NULL;
	return (split);
}

char	**ft_splitspace(const char *s)
{
	size_t	segnum;
	char	**splited;

	if (!s)
		return (NULL);
	segnum = segcount(s);
	splited = malloc((segnum + 1) * sizeof(char *));
	if (!splited)
		return (NULL);
	spliter(splited, s);
	return (splited);
}
