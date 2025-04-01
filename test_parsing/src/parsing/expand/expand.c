/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:29:49 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/01 13:43:50 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	condition_for_expand(t_list *token, char str)
{
	if ((((t_token *)token->content)->quote != SQUOTE)
		&& (!str || (str && ft_strncmp(str, "<<", 2) != 0)))
		return (OK);
	return (KO);
}

static int	has_dollars(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '$')
			return (OK);
	return (KO);
}

static int	start_expanding(t_shell *shell, char ***dollar_tab, char **str)
{
	
}

static	int	expand(t_shell *shell, t_list *token)
{
	t_list	*tmp;
	char	**dollar_tab;
	char	*str_before;

	tmp = token;
	str_before = NULL;
	while (tmp)
	{
		if (condition_for_expand(tmp, str_before) == OK)
			if (has_dollars(((t_token *)tmp->content)->str) == OK)
				if (start_expand(shell, &dollar_tab,
						&((t_token *)tmp->content)->str) == KO)
					return (KO);
		str_before = ((t_token *)tmp->content)->str;
		tmp = tmp->next;
	}
	return (KO);
}

int	parser_set(t_shell *shell, t_list *token, char *input)
{
	(void)input;
	if (expand(shell, token) == KO)
		return (KO);
	return (OK);
}
