/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:08:30 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/12 11:01:48 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_freetab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (tab);
}

void	fsplit(char **split, size_t j)
{
	while (j--)
	{
		if (split[j])
		{
			free(split[j]);
			split[j] = NULL;
		}
	}
	free(split);
}

t_cmd	*free_cmd(t_cmd *head)
{
	t_cmd	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->cmd_list)
			tmp->cmd_list = ft_freetab(tmp->cmd_list);
		if (tmp->infile)
			tmp->infile = ft_freetab(tmp->infile);
		if (tmp->outfile)
			tmp->outfile = ft_freetab(tmp->outfile);
		if (tmp->limiters)
			tmp->limiters = ft_freetab(tmp->limiters);
		free(tmp);
		tmp = NULL;
	}
	free(head);
	return (NULL);
}

void	free_all(t_shell *shell, char *emsg, int ecode)
{
	if (shell->cmd)
		shell->cmd = free_cmd(shell->cmd);
	if (emsg)
		printf("%s", emsg);
	if (ecode != -1)
	{
		ft_freetab(shell->env);
		rl_clear_history();
		exit(ecode);
	}
}
