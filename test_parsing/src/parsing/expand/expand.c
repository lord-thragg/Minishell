/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:29:49 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/01 17:56:43 by luluzuri         ###   ########.fr       */
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

static int	has_multdollars(char **str)
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

static char	*no_surround(char *str, t_shell *shell)
{
	
}

static char	*create_expand_dollar(t_shell *shell, char *str,
	char *expanded, int qtype)
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
		if (ft_strncmp(str, '?', 1) == 0)
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

static char	*dollar_expension(char *str, int qtype, t_shell *shell)
{
	char	*expanded;

	expanded = NULL;
	if (!str || !str[0] != '$')
	{
		expanded = ft_strdup("");
		if (!expanded)
			return (ft_putstr_fd(ER_MALLOC, 2), NULL);
		return (expanded);
	}
	if (str[1] == '\0')
	{
		expanded = ft_strdup("$");
		if (!expanded)
			return (ft_putstr_fd(ER_MALLOC, 2), NULL);
		return (expanded);
	}
	return (create_expand_dollar(shell, str, expanded, qtype));
}

static int	build_single(t_shell *shell, char **dollar, char **exported)
{
	*dollar = ft_strdup((*exported));
	if (!(*dollar))
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	(free(*exported), exported = NULL);
	*exported = dollar_expension(*dollar, DQUOTE, shell);
	if (!(*exported))
		return (free(*dollar), KO);
	(free(*dollar), dollar = NULL);
	return (OK);
}

static int	set_dollarNexpand(t_shell *shell, char ***dollar_tab, char ***exported)
{
	char	*dollar;
	int		y;

	y = -1;
	while ((*exported)[++y])
	{
		if ((*exported)[y][0] == '$' && has_multdollars((*exported)[y]) == KO)
		{
			if (buidl_single(shell, &dollar, &(*exported)[y]) == KO)
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

static int	start_expanding(t_shell *shell, char ***dollar_tab, char **str)
{
	char	*str_expanded;
	char	**exported;

	str_expanded = ft_strdup(*str);
	if (!str_expanded)
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	exported = ft_splitspaces(str_expanded);
	if (!exported)
	{
		(free(str_expanded), str_expanded = NULL);
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	}
	if (set_dollarsNexpande(shell, dollar_tab, &exported) == KO)
	{
		(free_tab(exported), exported = NULL);
		return (free(str_expanded), str_expanded = NULL, KO);
	}
	if (build_expandNreplace(&str_expanded, &exported, str) == KO)
		return (KO);
	return (OK);
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
