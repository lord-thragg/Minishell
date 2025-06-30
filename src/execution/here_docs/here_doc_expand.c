/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 16:55:09 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/19 17:01:32 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_and_free(char *s1, char *s2)
{
	char	*res;

	res = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (res);
}

static char	*expand_env_var(char *str, int *i, t_shell *shell)
{
	int		start;
	char	*key;
	char	*value;

	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(shell->ecode));
	}
	start = *i;
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	key = ft_substr(str, start, *i - start);
	if (!key)
		return (NULL);
	value = ft_getenv(key, shell);
	free(key);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

char	*expand_line(char *line, t_shell *shell)
{
	int		i;
	int		start;
	char	*result;
	char	*before;

	i = 0;
	start = 0;
	result = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$')
		{
			before = ft_substr(line, start, i - start);
			result = strjoin_and_free(result, before);
			result = strjoin_and_free(result, expand_env_var(line, &i, shell));
			start = i;
		}
		else
			i++;
	}
	if (i > start)
		result = strjoin_and_free(result, ft_substr(line, start, i - start));
	return (result);
}
