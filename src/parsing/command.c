/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:52:14 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/18 09:02:36 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	count_token(t_token *token)
{
	int		i;
	t_token	*tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}*/

void	add_cmd(t_cmd **head, t_cmd *ncmd)
{
	t_cmd	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = ncmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ncmd;
	ncmd->prev = tmp;
}

t_cmd	*token_to_command(t_token *token)
{
	t_cmd	*head;
	t_cmd	*ncmd;
	int		i;

	i = 0;
	head = NULL;
	ncmd = NULL;
	while (token)
	{
		if (!ncmd)
		{
			ncmd = (t_cmd *)malloc(sizeof(t_cmd));
			if (ncmd == NULL)
				return (NULL);
			ncmd->cmd_list = (char *)malloc(2 * sizeof(char));
			if (!ncmd->cmd_list)
				return (NULL);
		}
		if (token->type == PIPE)
			add_cmd(&head, ncmd);
	}
	free_token(token);
	return (head);
}
