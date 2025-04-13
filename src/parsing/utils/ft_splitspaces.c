/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 14:35:21 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/12 12:38:50 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*alloc_token(const char *start, int len)
{
	char	*token;
	int		i;

	token = (char *)malloc(len + 1);
	if (!token)
		return (NULL);
	i = 0;
	while (i < len)
	{
		token[i] = start[i];
		i++;
	}
	token[len] = '\0';
	return (token);
}

char	**free_tokens(char **result, int i)
{
	while (i > 0)
		free(result[--i]);
	free(result);
	return (NULL);
}

char	*get_next_token(const char **s, int *len)
{
	const char	*start;

	if (is_space(**s))
	{
		*len = 1;
		start = *s;
		(*s)++;
	}
	else
	{
		start = *s;
		*len = 0;
		while (**s && !is_space(**s))
		{
			(*s)++;
			(*len)++;
		}
	}
	return ((char *)start);
}

char	**fill_tokens(const char *s, char **result, int tokens_count)
{
	int		i;
	int		len;
	char	*start;

	i = 0;
	while (i < tokens_count && *s)
	{
		start = get_next_token(&s, &len);
		result[i] = alloc_token(start, len);
		if (!result[i])
			return (free_tokens(result, i));
		i++;
	}
	result[i] = NULL;
	return (result);
}

char	**ft_splitspaces(const char *s)
{
	char	**result;
	int		tokens_count;

	if (!s)
		return (NULL);
	tokens_count = count_tokens(s);
	result = (char **)malloc(sizeof(char *) * (tokens_count + 1));
	if (!result)
		return (NULL);
	return (fill_tokens(s, result, tokens_count));
}
