/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 13:29:49 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/02 10:11:24 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	condition_for_expand(t_list *token, char *str)
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

static int	has_multdollars(char *str)
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

static char	*keep_next_str(char **str)
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

static char	*no_surround(char *str, t_shell *shell)
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
			expanded = ft_strjoin(expanded, next_str);
			(free(next_str), next_str = NULL);
			if (!expanded)
				return (ft_putstr_fd(ER_MALLOC, 2), NULL);
			return (expanded);
		}
	}
	expanded = ft_strjoin(expanded, next_str);
	if (!expanded)
		return (free(next_str), next_str = NULL,
			ft_putstr_fd(ER_MALLOC, 2), NULL);
	return (free(next_str), next_str = NULL, expanded);
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

static char	*dollar_expension(char *str, int qtype, t_shell *shell)
{
	char	*expanded;

	expanded = NULL;
	if (!str || !(str[0] != '$'))
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
	(free(*exported), *exported = NULL);
	*exported = dollar_expension(*dollar, DQUOTE, shell);
	if (!(*exported))
		return (free(*dollar), KO);
	(free(*dollar), *dollar = NULL);
	return (OK);
}

static int	no_otab(char ***original_tab, char *toadd, char ***newtab)
{
	if (!(*original_tab))
	{
		*newtab = ft_calloc(2, sizeof(char *));
		if (!newtab)
			return (ft_putstr_fd(ER_MALLOC, 2), KO);
		(*newtab)[0] = ft_strdup(toadd);
		if (!(*newtab)[0])
		{
			ft_freetab(*original_tab);
			*original_tab = NULL;
			return (ft_putstr_fd(ER_MALLOC, 2), KO);
		}
		(*newtab)[1] = NULL;
		(*original_tab) = (*newtab);
		return (OK);
	}
	return (OK);
}

static int	countcopy_otab(char ***original, char ***newtab, int *ntab)
{
	(*ntab) = 0;
	while ((*original)[(*ntab)])
		(*ntab)++;
	(*newtab) = ft_calloc((*ntab) + 2, sizeof(char *));
	if (!newtab)
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	(*ntab) = -1;
}

static int	add_back_tab(char ***dollar_tab, char *toadd)
{
	int		ntab;
	char	**newtab;

	newtab = NULL;
	if (!(*dollar_tab))
		return (no_otab(dollar_tab, toadd, &newtab));
	if (countcopy_otab(dollar_tab, &newtab, &ntab) == KO)
		return (KO);
	if (toadd)
	{
		newtab[ntab] = ft_strdup(toadd);
		if (!newtab)
		{
			ft_freetab(*dollar_tab);
			*dollar_tab = NULL;
			return (ft_putstr_fd(ER_MALLOC, 2), KO);
		}
		ntab++;
	}
	newtab[ntab] = NULL;
	ft_freetab(*dollar_tab);
	(*dollar_tab) = newtab;
	return (OK);
}

static int	fstep_multdollar(t_shell *shell, char ***dollar_tab, char **exported)
{
	(*dollar_tab) = ft_split((*exported), '$');
	if (!(*dollar_tab))
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	if ((*exported)[ft_strlen(*exported) - 1] == '$')
		if (add_back_tab(dollar_tab, "") == KO)
			return (KO);
	if (!(*dollar_tab)[0])
	{
		free((*exported));
		(*exported) = 0;
		(*exported) = ft_strdup("");
		if (!(*exported))
		{
			ft_freetab(*dollar_tab);
			return (ft_putstr_fd(ER_MALLOC, 2), KO);
		}
		else if (add_doll_tab(shell, dollar_tab, (*exported)) == KO)
			return (ft_freetab(*dollar_tab), KO);
		return (OK);
	}
}

static int	handle_multdollar(t_shell *shell, char ***dollar_tab, char **exported)
{
	int	z;

	if (fstep_multdollar(shell, dollar_tab, exported) == KO)
		return (KO);
	free((*exported));
	z = -1;
	(*exported) = ft_strdup("");
	if (!(*exported))
	{
		ft_freetab(*dollar_tab);
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	}
	while ((*dollar_tab)[++z])
	{
		(*exported) = ft_strjoin((*exported), (*dollar_tab)[z]);
		if (!(*exported))
		{
			ft_freetab(*dollar_tab);
			return (ft_putstr_fd(ER_MALLOC, 2), KO);
		}
		ft_freetab(*dollar_tab);
		return (OK);
	}
}

static int	set_dollarsNexpande(t_shell *shell, char ***dollar_tab,
	char ***exported)
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

static int	build_expandNreplace(char **str_expanded, char ***exported,
	char *str)
{
	int	y;

	y = -1;
	(free(*str_expanded), *str_expanded = NULL);
	while ((*exported)[++y])
	{
		(*str_expanded) = ft_strjoin((*str_expanded), (*exported)[y]);
		if (!(*str_expanded))
			return (ft_putstr_fd(ER_MALLOC, 2), KO);
	}
	ft_freetab(*exported);
	if ((*str_expanded)[0] != '\0' && \
		(*str_expanded)[ft_strlen((*str_expanded)) - 1] == ' ')
		(*str_expanded)[ft_strlen((*str_expanded)) - 1] = '\0';
	free(str);
	*str = NULL;
	*str = ft_strdup((*str_expanded));
	if (!*str)
	{
		(free(*str_expanded), *str_expanded = NULL);
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	}
	(free(*str_expanded), *str_expanded = NULL);
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
		(ft_freetab(exported), exported = NULL);
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
