/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:04:36 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/12 12:32:35 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_space(char **prompt_loop, t_list **token, char buffer[BSIZE])
{
	t_token	*last;

	if (ft_strlen(buffer) > 0)
	{
		add_token(token, buffer);
		last = ft_lstlast(*token)->content;
		if (last->str[0] == '-')
			last->type = ARG;
		ft_bzero(buffer, BSIZE);
	}
	(*prompt_loop)++;
}

void	set_optype(t_token *token)
{
	if (token->str[0] == '|')
		token->type = PIPE;
	else if (ft_strncmp(token->str, "<<", 2) == 0)
		token->type = HEREDOC;
	else if (ft_strncmp(token->str, ">>", 2) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->str, ">", 1) == 0)
		token->type = REDOUT;
	else if (ft_strncmp(token->str, "<", 1) == 0)
		token->type = REDIN;
}

void	handle_operator(char **loop, t_list **token, char buffer[BSIZE])
{
	if (ft_strlen(buffer) > 0)
	{
		add_token(token, buffer);
		ft_bzero(buffer, BSIZE);
	}
	buffer[0] = **loop;
	(*loop)++;
	if (**loop == buffer[0])
	{
		buffer[1] = **loop;
		(*loop)++;
	}
	add_token(token, buffer);
	set_optype(ft_lstlast(*token)->content);
	ft_bzero(buffer, BSIZE);
}

int	process(char **loop, t_list **token, char *buffer, int *i)
{
	if (*i == BSIZE)
	{
		if (hoverflow(token) != OK)
			return (KO);
		*i = 0;
	}
	else if (**loop == 34 || **loop == 39)
	{
		if (handle_quotes(loop, token, buffer) == KO)
			return (KO);
		*i = 0;
	}
	else if (check_operator(*loop) == OK)
	{
		handle_operator(loop, token, buffer);
		*i = 0;
	}
	else if (**loop == ' ' || **loop == '\t')
	{
		handle_space(loop, token, buffer);
		*i = 0;
	}
	else
		increments(loop, buffer, i);
	return (OK);
}

int	tokenize(t_list **token, char *input)
{
	int		i;
	char	*loop;
	char	buffer[BSIZE];

	i = 0;
	ft_bzero(buffer, BSIZE);
	loop = input;
	while (*loop)
	{
		if (process(&loop, token, buffer, &i) == KO)
			return (KO);
	}
	if (ft_strlen(buffer) > 0)
		add_token(token, buffer);
	return (OK);
}
