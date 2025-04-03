/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 16:08:30 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/03 11:45:35 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/*t_token	*free_token(t_token *head)
{
	t_token	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		if (tmp->str != NULL)
			free(tmp->str);
		free(tmp);
		tmp = NULL;
	}
	free(head);
	return (NULL);
}*/

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
/*	if (shell->token)
		shell->token = free_token(shell->token);*/
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
