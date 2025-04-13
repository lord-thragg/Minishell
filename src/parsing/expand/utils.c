/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:21:02 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/12 12:26:17 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_doll_ftab(t_shell *shell, char ***dollar_tab)
{
	char	*add_fdol;
	char	*tmp_expanded;

	add_fdol = ft_strdup("$");
	if (!add_fdol)
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	add_fdol = strjoin_free(add_fdol, (*dollar_tab)[0]);
	if (!add_fdol)
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	tmp_expanded = dollar_expension(add_fdol, DQUOTE, shell);
	if (!tmp_expanded)
		return (free(add_fdol), KO);
	free(add_fdol);
	add_fdol = 0;
	free((*dollar_tab)[0]);
	(*dollar_tab)[0] = 0;
	(*dollar_tab)[0] = ft_strdup(tmp_expanded);
	if (!(*dollar_tab)[0])
	{
		free(tmp_expanded);
		return (ft_putstr_fd(ER_MALLOC, 2), KO);
	}
	free(tmp_expanded);
	return (OK);
}

int	do_expansion(t_shell *shell, char **dollar_tab)
{
	char	*tmp_expanded;
	char	*tmp;

	tmp = ft_strdup("$");
	if (!tmp)
		return (ft_putstr_fd(ER_MALLOC, STDERR_FILENO), KO);
	tmp = strjoin_free(tmp, (*dollar_tab));
	if (!tmp)
		return (ft_putstr_fd(ER_MALLOC, STDERR_FILENO), KO);
	tmp_expanded = dollar_expension(tmp, DQUOTE, shell);
	if (!tmp_expanded)
		return (free(tmp), KO);
	free(tmp);
	tmp = 0;
	free((*dollar_tab));
	*dollar_tab = 0;
	(*dollar_tab) = ft_strdup(tmp_expanded);
	if (!(*dollar_tab))
	{
		free(tmp_expanded);
		return (ft_putstr_fd(ER_MALLOC, STDERR_FILENO), KO);
	}
	free(tmp_expanded);
	tmp_expanded = 0;
	return (OK);
}

int	add_doll_tab(t_shell *shell, char ***dollar_tab, char *exported)
{
	int	i;

	if (exported[0] == '$')
		if (add_doll_ftab(shell, dollar_tab) == KO)
			return (KO);
	i = 0;
	while ((*dollar_tab)[++i])
		if (do_expansion(shell, &(*dollar_tab)[i]) == KO)
			return (KO);
	return (OK);
}

int	fstep_multdollar(t_shell *shell, char ***dollar_tab, char **exported)
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
	}
	else if (add_doll_tab(shell, dollar_tab, (*exported)) == KO)
		return (ft_freetab(*dollar_tab), KO);
	return (OK);
}

int	handle_multdollar(t_shell *shell, char ***dollar_tab, char **exported)
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
		(*exported) = strjoin_free((*exported), (*dollar_tab)[z]);
		if (!(*exported))
		{
			ft_freetab(*dollar_tab);
			return (ft_putstr_fd(ER_MALLOC, 2), KO);
		}
	}
	ft_freetab(*dollar_tab);
	return (OK);
}
