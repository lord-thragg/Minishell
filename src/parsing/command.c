/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:52:14 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/23 17:07:55 by luluzuri         ###   ########.fr       */
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

static int	cheredoc(t_token *token)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == HEREDOC)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

static t_cmd	*create_cmd(t_cmd *ncmd, t_token *token)
{
	int	i;

	i = 0;
	if (ncmd)
		return (ncmd);
	ncmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!ncmd)
		return (NULL);
	ncmd->cmd_list = (char **)malloc((3 + cheredoc(token)) * sizeof(char *));
	if (!ncmd->cmd_list)
		return (NULL);
	while (i < (3 + cheredoc(token)))
	{
		ncmd->cmd_list[i] = NULL;
		i++;
	}
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
	t_token	*tmp;
	t_cmd	*head;
	t_cmd	*ncmd;

	head = NULL;
	ncmd = NULL;
	tmp = token;
	while (tmp)
	{
		ncmd = create_cmd(ncmd, tmp);
		if (!ncmd)
			return (NULL);
		tmp = determine_type(&head, &ncmd, tmp);
		if (!tmp)
			return (NULL);
		tmp = tmp->next;
	}
	if (tmp == NULL)
	{
		add_cmd(&head, ncmd);
		ncmd = NULL;
	}
	free_token(token);
	return (head);
}
