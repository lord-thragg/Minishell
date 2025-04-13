/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:22:13 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/12 12:35:50 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	has_dollars(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			return (OK);
	return (KO);
}

int	has_multdollars(char *str)
{
	int	i;
	int	dollars;

	i = -1;
	dollars = 0;
	while (str[++i])
		if (str[i] == '$')
			dollars++;
	if (dollars > 1)
		return (OK);
	return (KO);
}

char	*keep_next_str(char **str)
{
	char	*next_str;
	int		i;

	i = -1;
	while ((*str)[++i])
		if (ft_isalnum((*str)[i]) == 0 && (*str)[i] != '_')
			break ;
	next_str = ft_strdup(*str + i);
	(*str)[i] = '\0';
	return (next_str);
}

char	*no_surround(char *str, t_shell *shell)
{
	char	*expanded;
	char	*next_str;
	int		i;

	expanded = NULL;
	i = -1;
	next_str = keep_next_str(&str);
	while (shell->env[++i])
	{
		if (ft_strncmp(shell->env[i], str, ft_strlen(str)) == 0
			&& shell->env[i][ft_strlen(str)] == '=')
		{
			expanded = ft_strdup(shell->env[i] + ft_strlen(str) + 1);
			expanded = strjoin_free(expanded, next_str);
			(free(next_str), next_str = NULL);
			if (!expanded)
				return (ft_putstr_fd(ER_MALLOC, 2), NULL);
			return (expanded);
		}
	}
	expanded = strjoin_free(expanded, next_str);
	if (!expanded)
		return (free(next_str), next_str = NULL, ft_putstr_fd(ER_MALLOC, 2),
			NULL);
	return (free(next_str), next_str = NULL, expanded);
}

char	*create_expand_dollar(t_shell *shell, char *str, char *expanded,
		int qtype)
{
	if (qtype == SQUOTE)
	{
		expanded = ft_strdup(str);
		if (!expanded)
			return (ft_putstr_fd(ER_MALLOC, 2), NULL);
	}
	else
	{
		str++;
		if (ft_strncmp(str, "?", 1) == 0)
		{
			expanded = ft_itoa(shell->ecode);
			if (!expanded)
				return (ft_putstr_fd(ER_MALLOC, 2), NULL);
		}
		else
		{
			return (no_surround(str, shell));
		}
	}
	return (expanded);
}
