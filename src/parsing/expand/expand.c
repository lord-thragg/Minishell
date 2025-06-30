/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:29:49 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/19 15:14:57 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_dollarsnexpande(t_shell *shell, char ***dollar_tab, char ***exported)
{
	char	*dollar;
	int		y;

	y = -1;
	while ((*exported)[++y])
	{
		if ((*exported)[y][0] == '$' && has_multdollars((*exported)[y]) == KO)
		{
			if (build_single(shell, &dollar, &(*exported)[y]) == KO)
				return (KO);
		}
		else if (has_dollars((*exported)[y]) == OK)
		{
			if (handle_multdollar(shell, dollar_tab, &(*exported)[y]) == KO)
				return (KO);
		}
	}
	return (OK);
}

int	build_expandnreplace(char **str_expanded, char ***exported, char **str)
{
	int	y;

	y = -1;
	(free(*str_expanded), *str_expanded = NULL);
	y = -1;
	while ((*exported)[++y])
	{
		(*str_expanded) = strjoin_free((*str_expanded), (*exported)[y]);
		if (!(*str_expanded))
			return (ft_putstr_fd(ER_MALLOC, 2), KO);
	}
	ft_freetab(*exported);
	if ((*str_expanded)[0] != '\0' && (*str_expanded)[ft_strlen((*str_expanded))
		- 1] == ' ')
		(*str_expanded)[ft_strlen((*str_expanded)) - 1] = '\0';
	free(*str);
	*str = NULL;
	*str = ft_strdup((*str_expanded));
	if (!(*str))
	{
		(free(*str_expanded), *str_expanded = NULL);
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	}
	(free(*str_expanded), *str_expanded = NULL);
	return (OK);
}

int	start_expanding(t_shell *shell, char ***dollar_tab, char **str)
{
	char	*str_expanded;
	char	**exported;

	if (ft_strcmp(*str, "$$") == 0)
		return (expand_pid(str), OK);
	str_expanded = ft_strdup(*str);
	if (!str_expanded)
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	exported = ft_splitspaces(str_expanded);
	if (!exported)
	{
		(free(str_expanded), str_expanded = NULL);
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	}
	if (set_dollarsnexpande(shell, dollar_tab, &exported) == KO)
	{
		(ft_freetab(exported), exported = NULL);
		return (free(str_expanded), str_expanded = NULL, KO);
	}
	if (build_expandnreplace(&str_expanded, &exported, str) == KO)
		return (KO);
	return (OK);
}

int	expand(t_shell *shell, t_list **token)
{
	t_list	*tmp;
	char	**dollar_tab;
	char	*str_before;

	tmp = *token;
	str_before = NULL;
	while (tmp)
	{
		if (condition_for_expand(tmp, str_before) == OK)
		{
			if (has_dollars(((t_token *)tmp->content)->str) == OK)
			{
				if (start_expanding(shell, &dollar_tab,
						&((t_token *)tmp->content)->str) == KO)
					return (KO);
			}
		}
		if (tmp->next == NULL)
			break ;
		str_before = ((t_token *)tmp->content)->str;
		tmp = tmp->next;
	}
	merge_joined_tokens(token);
	return (OK);
}

int	parser_set(t_shell *shell, t_list *token, char *input)
{
	(void)input;
	if (expand(shell, &token) == KO)
		return (KO);
	return (OK);
}
