/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:52:14 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/18 09:40:57 by luluzuri         ###   ########.fr       */
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

static void	add_cmd(t_cmd **head, t_cmd *ncmd)
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

static void	*detect_type(t_cmd **cmd, t_token *token)
{
	
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
		ncmd = create_cmd(ncmd);
		if (!ncmd)
			return (NULL);
		if (token->type == CMD)
		{
			ncmd->cmd_list[i] = ft_strdup(token->str);
			if (!ncmd->cmd_list[i])
				return (NULL);
			i++;
		}
		if (token->type == PIPE)
		{
			add_cmd(&head, ncmd);
			ncmd = NULL;
		}
	}
	free_token(token);
	return (head);
}
