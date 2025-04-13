/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:12:30 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/12 13:26:02 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*outfile(t_cmd *cmd, t_list *token)
{
	if (!token->next || !((t_token *)token->next->content)->str)
		return (NULL);
	cmd->outfile = append_str(cmd->outfile,
			((t_token *)token->next->content)->str);
	if (!cmd->outfile)
		return (NULL);
	if (((t_token *)token->content)->type == APPEND)
		cmd->append = true;
	else
		cmd->append = false;
	return (token->next);
}

t_list	*infile_outfile(t_cmd *cmd, t_list *token)
{
	if (((t_token *)token->content)->type == REDOUT
		|| ((t_token *)token->content)->type == APPEND)
	{
		return (outfile(cmd, token));
	}
	if (((t_token *)token->content)->type == REDIN)
	{
		cmd->last = 0;
		if (!token->next || !((t_token *)token->next->content)->str)
			return (NULL);
		cmd->infile = append_str(cmd->infile,
				((t_token *)token->next->content)->str);
		if (!cmd->infile)
			return (NULL);
		return (token->next);
	}
	return (NULL);
}

t_list	*file_type(t_cmd *cmd, t_list *token)
{
	int	i;

	if (((t_token *)token->content)->type == REDOUT
		|| ((t_token *)token->content)->type == APPEND
		|| ((t_token *)token->content)->type == REDIN)
		return (infile_outfile(cmd, token));
	if (((t_token *)token->content)->type == HEREDOC)
	{
		cmd->last = 1;
		i = 0;
		while (cmd->limiters[i])
			i++;
		if (!token->next || !((t_token *)token->next->content)->str)
			return (NULL);
		cmd->limiters[i] = ft_strdup(((t_token *)token->next->content)->str);
		return (token->next);
	}
	return (NULL);
}

t_list	*arg_type(t_cmd **cmd, t_list *token)
{
	int	i;

	i = 0;
	while ((*cmd)->cmd_list[i])
		i++;
	(*cmd)->cmd_list[i] = ft_strdup(((t_token *)token->content)->str);
	if (!(*cmd)->cmd_list[i])
		return (NULL);
	return (token);
}

int	ctype(t_list *token, int flag)
{
	t_list	*tmp;
	int		count;

	count = 0;
	tmp = token;
	while (tmp)
	{
		if (((t_token *)tmp->content)->type == flag)
			count++;
		tmp = tmp->next;
	}
	return (count);
}
