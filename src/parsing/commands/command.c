/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:07:21 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/19 14:51:04 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**initiate_file(t_list *token, int flag)
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

int	ctoken(t_list *tok)
{
	t_list	*tmp;
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

t_cmd	*create_cmd(t_cmd *ncmd, t_list *token)
{
	if (ncmd)
		return (ncmd);
	ncmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!ncmd)
		return (NULL);
	ncmd->last = -1;
	ncmd->cmd_list = (char **)malloc((ctoken(token) + 1) * sizeof(char *));
	if (!ncmd->cmd_list)
		return (NULL);
	put_null(ncmd->cmd_list, ctoken(token) + 1);
	ncmd->limiters = (char **)malloc((ctype(token, HEREDOC) + 1)
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
	ncmd->next = NULL;
	return (ncmd);
}

t_list	*determine_type(t_cmd **head, t_cmd **cmd, t_list *token)
{
	t_list	*tmp;

	tmp = NULL;
	if (((t_token *)token->content)->type == CMD)
	{
		(*cmd)->cmd_list[0] = ft_strdup(((t_token *)token->content)->str);
		if (!(*cmd)->cmd_list[0])
			return (NULL);
		return (token);
	}
	if (((t_token *)token->content)->type == ARG)
		return (arg_type(cmd, token));
	tmp = file_type(*cmd, token);
	if (!tmp && ((t_token *)token->content)->type != PIPE)
		return (NULL);
	if (tmp)
		return (tmp);
	if (((t_token *)token->content)->type == PIPE && token->next != NULL)
	{
		add_cmd(head, *cmd);
		(*cmd) = NULL;
		return (token);
	}
	return (NULL);
}

t_cmd	*token_to_command(t_list *token)
{
	t_list	*tmp;
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
	return (head);
}
