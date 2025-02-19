/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:52:14 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/19 16:35:00 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*static int	count_token(t_token *token)
{
	int		i;
	t_token	*tmp;
	t_cmd	*tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}*/
static void	add_cmd(t_cmd **head, t_cmd *ncmd)
{
	t_token	*tmp;

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

static t_cmd	*create_cmd(t_cmd *ncmd)
{
	if (ncmd)
		return (ncmd);
	ncmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (ncmd == NULL)
		return (NULL);
	ncmd->cmd_list = (char *)malloc(2 * sizeof(char));
	if (!ncmd->cmd_list)
		return (NULL);
	return (ncmd);
}

t_cmd	*token_to_command(t_token *token)
{
	t_cmd	*head;
	t_cmd	*ncmd;
	t_token	*tmp;
	int		i;

	i = 0;
	head = NULL;
	ncmd = NULL;
	tmp = token;
	while (tmp)
	{
		ncmd = create_cmd(ncmd);
		if (!ncmd)
			return (NULL);
		tmp = detect_type(head, ncmd, tmp);
		tmp = tmp->next;
	}
	free_token(token);
	return (head);
}
