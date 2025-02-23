/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:15 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/23 10:45:48 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static t_token	*file_type(t_cmd *cmd, t_token *token)
{
	if (token->type == REDOUT || token->type == APPEND)
	{
		cmd->outfile = ft_strdup(token->next->str);
		if (token->type == APPEND)
			cmd->append = true;
		return (token->next);
	}
	if (token->type == REDIN)
	{
		cmd->infile = ft_strdup(token->next->str);
		return (token->next);
	}
	if (token->type == HEREDOC)
	{
		printf("token->type == HEREDOC");
	}
	return (NULL);
}

t_token	*arg_type(t_cmd **cmd, t_token *token)
{
	t_cmd	*tmp;
	char	*tmp_str;

	tmp = *cmd;
	if (tmp->cmd_list[1] && tmp->cmd_list[1][0])
	{
		tmp_str = ft_strjoin(tmp->cmd_list[1], token->str);
		if (!tmp_str)
			return (NULL);
		free(tmp->cmd_list[1]);
		tmp->cmd_list[1] = tmp_str;
	}
	else
	{
		tmp->cmd_list[1] = ft_strdup(token->str);
		if (!tmp->cmd_list[1])
			return (NULL);
	}
	cmd = &tmp;
	return (token);
}

t_token	*determine_type(t_cmd **head, t_cmd *cmd, t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	if (token->type == CMD)
	{
		cmd->cmd_list[0] = ft_strdup(token->str);
		if (!cmd->cmd_list[0])
			return (NULL);
		return (token);
	}
	if (token->type == ARG)
		return (arg_type(&cmd, token));
	tmp = file_type(cmd, token);
	if (tmp)
		return (tmp);
	if (token->type == PIPE || token->next == NULL)
	{
		add_cmd(head, cmd);
		cmd = NULL;
		return (token);
	}
	return (NULL);
}
