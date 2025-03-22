/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitspace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 08:39:35 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/22 13:38:52 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_tab(char **splited)
{
	for (int i = 0; splited[i]; i++)
		printf("%s\n", splited[i]);
}

static char	*ft_strndup(const char *s, size_t n)
{
	char	*res;

	res = malloc(n + 1);
	if (!res)
		return (NULL);
	memcpy(res, s, n);
	res[n] = '\0';
	return (res);
}

static size_t	segcount(const char *s)
{
	size_t	i = 0;
	size_t	segnum = 0;

	while (s[i])
	{
		/* Ignorer espaces et tabulations */
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
			break;
		/* Si le segment commence par un guillemet simple ou double */
		if (s[i] == '\'' || s[i] == '"')
		{
			char quote = s[i];
			i++;  // passer le guillemet ouvrant
			while (s[i] && s[i] != quote)
				i++;
			if (s[i] == quote)
				i++;  // passer le guillemet fermant
			segnum++;
		}
		else if (s[i] == '|')
		{
			segnum++;
			i++;
		}
		else
		{
			while (s[i] && s[i] != ' ' && s[i] != '\t'
				&& s[i] != '\'' && s[i] != '"' && s[i] != '|')
				i++;
			segnum++;
		}
	}
	return (segnum);
}

static char	**spliter(char **split, const char *s)
{
	size_t	i = 0;
	size_t	j = 0;
	size_t	start;

	while (s[i])
	{
		/* Ignorer espaces et tabulations */
		while (s[i] == ' ' || s[i] == '\t')
			i++;
		if (!s[i])
			break;
		/* Si le segment commence par un guillemet simple ou double */
		if (s[i] == '\'' || s[i] == '"')
		{
			char quote = s[i];
			/* Pour les guillemets simples, on garde les quotes */
			if (quote == '\'')
			{
				start = i;  // inclure le guillemet ouvrant
				i++;  // passer le guillemet ouvrant
				while (s[i] && s[i] != '\'')
					i++;
				if (s[i] == '\'')
					i++;  // inclure le guillemet fermant
				/* On garde le token avec les quotes */
				split[j++] = ft_strndup(s + start, i - start);
			}
			/* Pour les guillemets doubles, on ne garde pas les quotes */
			else if (quote == '"')
			{
				i++;  // passer le guillemet ouvrant
				start = i;
				while (s[i] && s[i] != '"')
					i++;
				/* On copie le contenu entre les quotes */
				split[j++] = ft_strndup(s + start, i - start);
				if (s[i] == '"')
					i++;  // passer le guillemet fermant
			}
		}
		else if (s[i] == '|')
		{
			split[j++] = ft_strndup("|", 1);
			i++;
		}
		else
		{
			start = i;
			while (s[i] && s[i] != ' ' && s[i] != '\t'
				&& s[i] != '\'' && s[i] != '"' && s[i] != '|')
				i++;
			split[j++] = ft_strndup(s + start, i - start);
		}
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
	print_tab(splited);
	return (splited);
}
