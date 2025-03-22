/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 16:22:15 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/12 10:43:09 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*infile_outfile(t_cmd *cmd, t_token *token)
{
	if (token->type == REDOUT || token->type == APPEND)
	{
		if (!token->next || !token->next->str)
			return (NULL);
		cmd->outfile = append_str(cmd->outfile, token->next->str);
		if (!cmd->outfile)
			return (NULL);
		if (token->type == APPEND)
			cmd->append = true;
		else
			cmd->append = false;
		return (token->next);
	}
	if (token->type == REDIN)
	{
		cmd->last = 0;
		if (!token->next || !token->next->str)
			return (NULL);
		cmd->infile = append_str(cmd->infile, token->next->str);
		if (!cmd->infile)
			return (NULL);
		return (token->next);
	}
	return (NULL);
}

static t_token	*file_type(t_cmd *cmd, t_token *token)
{
	int	i;

	if (token->type == REDOUT || token->type == APPEND || token->type == REDIN)
		return (infile_outfile(cmd, token));
	if (token->type == HEREDOC)
	{
		cmd->last = 1;
		i = 0;
		while (cmd->limiters[i])
			i++;
		cmd->limiters[i] = ft_strdup(token->next->str);
		return (token->next);
	}
	return (NULL);
}

t_token	*arg_type(t_cmd **cmd, t_token *token)
{
	int	i;

	i = 0;
	while ((*cmd)->cmd_list[i])
		i++;
	(*cmd)->cmd_list[i] = ft_strdup(token->str);
	if (!(*cmd)->cmd_list[i])
		return (NULL);
	return (token);
}

t_token	*determine_type(t_cmd **head, t_cmd **cmd, t_token *token)
{
	t_token	*tmp;

	tmp = NULL;
	if (token->type == CMD)
	{
		(*cmd)->cmd_list[0] = ft_strdup(token->str);
		if (!(*cmd)->cmd_list[0])
			return (NULL);
		return (token);
	}
	if (token->type == ARG)
		return (arg_type(cmd, token));
	tmp = file_type(*cmd, token);
	if (!tmp && token->type != PIPE)
		return (NULL);
	if (tmp)
		return (tmp);
	if (token->type == PIPE && token->next != NULL)
	{
		add_cmd(head, *cmd);
		(*cmd) = NULL;
		return (token);
	}
	return (NULL);
}
