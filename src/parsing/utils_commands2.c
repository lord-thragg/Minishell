/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 09:06:00 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/28 11:55:23 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rebuild_str(char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (tab[i])
	{
		tmp = ft_strjoin(tmp, tab[i]);
		i++;
	}
	return (tmp);
}

int	ctoken(t_token *tok)
{
	t_token	*tmp;
	int		i;

	tmp = tok;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**append_str(char **tab, char *str)
{
	char	**ret;
	int		i;

	ret = NULL;
	i = 0;
	while (tab[i])
		i++;
	ret = (char **)malloc((i + 2) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	while (tab[++i])
		ret[i] = ft_strdup(tab[i]);
	ret[i] = ft_strdup(str);
	ret[i + 1] = NULL;
	ft_freetab(tab);
	return (ret);
}

void	add_cmd(t_cmd **head, t_cmd *ncmd)
{
	t_cmd	*tmp;

	tmp = *head;
	if (!tmp)
	{
		ncmd->next = NULL;
		*head = ncmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ncmd;
	ncmd->next = NULL;
}
