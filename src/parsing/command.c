/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:52:14 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/20 14:21:48 by luluzuri         ###   ########.fr       */
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

static t_cmd	*create_cmd(t_cmd *ncmd)
{
	if (ncmd)
		return (ncmd);
	ncmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (ncmd == NULL)
		return (NULL);
	ncmd->cmd_list = (char **)malloc(2 * sizeof(char *));
	if (!ncmd->cmd_list)
		return (NULL);
	ncmd->skip_cmd = NULL;
	ncmd->infile = 0;
	ncmd->outfile = 0;
	ncmd->prev = NULL;
	ncmd->next = NULL;
	return (ncmd);
}

t_cmd	*token_to_command(t_token *token)
{
	t_cmd	*head;
	t_cmd	*ncmd;
	t_token	*tmp;

	head = NULL;
	ncmd = NULL;
	tmp = token;
	while (tmp)
	{
		ncmd = create_cmd(ncmd);
		if (!ncmd)
			return (NULL);
		tmp = typing(&head, ncmd, tmp);
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
	}
	free_token(token);
	return (head);
}
