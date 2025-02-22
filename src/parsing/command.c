/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:52:14 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/22 15:51:47 by luluzuri         ###   ########.fr       */
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

int	count_heredoc(t_token *token)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (token)
	{
		if (tmp->type == HEREDOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static t_cmd	*create_cmd(t_cmd *ncmd, t_token *token)
{
	if (ncmd)
		return (ncmd);
	ncmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (ncmd == NULL)
		return (NULL);
	ncmd->cmd_list = (char **)malloc((3 + count_heredoc(token)) \
										* sizeof(char *));
	if (!ncmd->cmd_list)
		return (NULL);
	ncmd->skip_cmd = NULL;
	ncmd->append = false;
	ncmd->infile = NULL;
	ncmd->outfile = NULL;
	ncmd->prev = NULL;
	ncmd->next = NULL;
	return (ncmd);
}

t_cmd	*token_to_command(t_token *token)
{
	t_cmd	*head;
	t_cmd	*ncmd;

	head = NULL;
	ncmd = NULL;
	while (token)
	{
		ncmd = create_cmd(ncmd, token);
		if (!ncmd)
			return (NULL);
		token = determine_type(&head, ncmd, token);
		if (!token)
			return (NULL);
		token = token->next;
	}
	free_token(token);
	return (head);
}
