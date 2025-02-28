/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 09:52:14 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/27 21:33:12 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ctype(t_token *token, int flag)
{
	t_token	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp)
	{
		if (tmp->type == flag)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

void	put_null(char **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		tab[i] = NULL;
}

char	**initiate_file(t_token *token, int flag)
{
	char	**tab;
	int		count;

	count = ctype(token, flag);
	tab = malloc((count + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	put_null(tab, count + 1);
	return (tab);
}

static t_cmd	*create_cmd(t_cmd *ncmd, t_token *token)
{
	if (ncmd)
		return (ncmd);
	ncmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!ncmd)
		return (NULL);
	ncmd->cmd_list = (char **)malloc(3 * sizeof(char *));
	if (!ncmd->cmd_list)
		return (NULL);
	put_null(ncmd->cmd_list, 3);
	ncmd->limiters = (char **)malloc((ctype(token, HEREDOC) + 1) \
	* sizeof(char *));
	if (!ncmd->limiters)
		return (NULL);
	put_null(ncmd->limiters, ctype(token, HEREDOC) + 1);
	ncmd->outfile = initiate_file(token, REDOUT);
	if (!ncmd->outfile)
		return (NULL);
	ncmd->infile = initiate_file(token, REDIN);
	if (!ncmd->infile)
		return (NULL);
	ncmd->append = false;
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
