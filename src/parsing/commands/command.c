/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:07:21 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/03 11:30:21 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*rebuild_str(char **tab)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = NULL;
	while (tab[i])
	{
		tmp = ft_strjoin(tmp, tab[i]);
		i++;
	}
	return (tmp);
}

char	**append_str(char **tab, char *str)
{
	char	**ret;
	int		i;

	ret = NULL;
	i = 0;
	while (tab[i])
		i++;
	ret = (char **)malloc((i + 2) * sizeof(char *));
	if (!ret)
		return (NULL);
	i = -1;
	while (tab[++i])
		ret[i] = ft_strdup(tab[i]);
	ret[i] = ft_strdup(str);
	ret[i + 1] = NULL;
	ft_freetab(tab);
	return (ret);
}

void	add_cmd(t_cmd **head, t_cmd *ncmd)
{
	t_cmd	*tmp;

	tmp = *head;
	if (!tmp)
	{
		ncmd->next = NULL;
		*head = ncmd;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ncmd;
	ncmd->next = NULL;
}

t_list	*infile_outfile(t_cmd *cmd, t_list *token)
{
	if (((t_token *)token->content)->type == REDOUT \
		|| ((t_token *)token->content)->type == APPEND)
	{
		if (!token->next || !((t_token *)token->next)->str)
			return (NULL);
		cmd->outfile = \
			append_str(cmd->outfile, ((t_token *)token->next)->str);
		if (!cmd->outfile)
			return (NULL);
		if (((t_token *)token->content)->type == APPEND)
			cmd->append = true;
		else
			cmd->append = false;
		return (token->next);
	}
	if (((t_token *)token->content)->type == REDIN)
	{
		cmd->last = 0;
		if (!token->next || !((t_token *)token->next)->str)
			return (NULL);
		cmd->infile = \
			append_str(cmd->infile, ((t_token *)token->next)->str);
		if (!cmd->infile)
			return (NULL);
		return (token->next);
	}
	return (NULL);
}

t_list	*file_type(t_cmd *cmd, t_list *token)
{
	int	i;

	if (((t_token *)token->content)->type == REDOUT || \
		((t_token *)token->content)->type == APPEND || \
		((t_token *)token->content)->type == REDIN)
		return (infile_outfile(cmd, token));
	if (((t_token *)token->content)->type == HEREDOC)
	{
		cmd->last = 1;
		i = 0;
		while (cmd->limiters[i])
			i++;
		if (!token->next || !((t_token *)token->next)->str)
			return (NULL);
		cmd->limiters[i] = \
			ft_strdup(((t_token *)token->next)->str);
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
	(*cmd)->cmd_list[i] \
		= ft_strdup(((t_token *)token->content)->str);
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

void	put_null(char **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		tab[i] = NULL;
}

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
