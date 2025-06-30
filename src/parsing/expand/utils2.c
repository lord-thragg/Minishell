/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:21:41 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/12 12:25:50 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*dollar_expension(char *str, int qtype, t_shell *shell)
{
	char	*expanded;

	expanded = NULL;
	if (!str || !(str[0] == '$'))
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

int	build_single(t_shell *shell, char **dollar, char **exported)
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

int	no_otab(char ***original_tab, char *toadd, char ***newtab)
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

int	countcopy_otab(char ***original, char ***newtab, int *ntab)
{
	(*ntab) = 0;
	while ((*original)[(*ntab)])
		(*ntab)++;
	(*newtab) = ft_calloc((*ntab) + 2, sizeof(char *));
	if (!newtab)
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	(*ntab) = -1;
	while ((*original)[++(*ntab)])
	{
		(*newtab)[(*ntab)] = ft_strdup((*original)[(*ntab)]);
		if (!(*newtab)[(*ntab)])
		{
			ft_freetab(*original);
			*original = NULL;
			return (ft_putstr_fd(ER_MALLOC, 2), KO);
		}
	}
	return (OK);
}

int	add_back_tab(char ***dollar_tab, char *toadd)
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
