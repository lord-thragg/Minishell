/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:39:35 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/24 14:46:51 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	split_single_quotes(char **split, const char *s, size_t *i,
		size_t *j)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (s[*i] && s[*i] != '\'')
		(*i)++;
	if (s[*i] == '\'')
		(*i)++;
	split[(*j)++] = ft_strndup(s + start, *i - start);
}

static void	split_double_quotes(char **split, const char *s, size_t *i,
		size_t *j)
{
	size_t	start;

	start = *i;
	(*i)++;
	while (s[*i] && s[*i] != '"')
		(*i)++;
	if (s[*i] == '"')
		(*i)++;
	split[(*j)++] = ft_strndup(s + start, *i - start);
}

static void	split_segments(char **split, const char *s, size_t *i, size_t *j)
{
	size_t	start;

	while (s[*i] == ' ' || s[*i] == '\t')
		(*i)++;
	if (!s[*i])
		return ;
	if (s[*i] == '\'')
		split_single_quotes(split, s, i, j);
	else if (s[*i] == '"')
		split_double_quotes(split, s, i, j);
	else if (s[*i] == '|')
	{
		split[(*j)++] = ft_strndup("|", 1);
		(*i)++;
	}
	else
	{
		start = *i;
		while (s[*i] && s[*i] != ' ' && s[*i] != '\t' && s[*i] != '\''
			&& s[*i] != '"' && s[*i] != '|')
			(*i)++;
		split[(*j)++] = ft_strndup(s + start, *i - start);
	}
}

static char	**spliter(char **split, const char *s)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s[i])
		split_segments(split, s, &i, &j);
	split[j] = NULL;
	return (split);
}

/*void	print_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
	{
		printf("sale fou ya pas de tab\n");
		return ;
	}
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}*/

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
