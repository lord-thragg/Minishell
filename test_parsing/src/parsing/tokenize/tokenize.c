/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:04:36 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/02 16:12:35 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hoverflow(t_list **token)
{
	ft_putstr_fd(ER_BUFF, 2);
	ft_lstclear_cust(token, free);
	return (2);
}

static int	twin_quote(char *str)
{
	int		i;
	char	quote;

	i = 1;
	quote = str[0];
	while (str[i])
	{
		if (str[i] == quote)
			return (OK);
		i++;
	}
	return (KO);
}

static char	*copy_to_twin(char **loop, char buffer[BSIZE])
{
	int		i;
	char	occ;

	i = 0;
	occ = **loop;
	(*loop)++;
	while (**loop != occ)
	{
		buffer[i] = **loop;
		i++;
		(*loop)++;
	}
	(*loop)++;
	return (buffer);
}

static void	add_token(t_list **token, char buffer[BSIZE])
{
	if (*token == NULL)
		*token = ft_lstnew_custom(buffer);
	else
		ft_lstadd_back(token, ft_lstnew_custom(buffer));
	return ;
}

int	check_quote_type(char **loop)
{
	if (**loop == 34)
		return (DQUOTE);
	else if (**loop == 39)
		return (SQUOTE);
	return (0);
}

static int	handle_quotes(char **loop, t_list **token, char buffer[BSIZE])
{
	int		quote;
	t_list	*last;
	t_token	*content;

	if (ft_strlen(buffer) > 0)
	{
		add_token(token, buffer);
		ft_bzero(buffer, BSIZE);
	}
	if (twin_quote(*loop) == OK)
	{
		quote = check_quote_type(loop);
		buffer = copy_to_twin(loop, buffer);
		add_token(token, buffer);
		last = ft_lstlast(*token);
		content = last->content;
		content->quote = quote;
		ft_bzero(buffer, BSIZE);
	}
	else
		return (ft_putstr_fd("Error: bad quotes.\n", 2), KO);
	return (OK);
}

static void	increments(char **prompt_loop, char *buffer, int *i)
{
	buffer[*i] = **prompt_loop;
	(*i)++;
	(*prompt_loop)++;
}

static int	check_operator(char *loop)
{
	if (ft_strncmp(loop, ">", 1))
		return (OK);
	if (ft_strncmp(loop, "<", 1))
		return (OK);
	if (ft_strncmp(loop, "|", 1))
		return (OK);
	return (KO);
}

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

static void	set_optype(t_token *token)
{
	if (token->str[0] == '|')
		token->type = PIPE;
	else if (ft_strncmp(token->str, "<<", 2) == 0)
		token->type = HEREDOC;
	else if (ft_strncmp(token->str, ">>", 2) == 0)
		token->type = APPEND;
	else if (ft_strncmp(token->str, ">", 2) == 0)
		token->type = REDOUT;
	else if (ft_strncmp(token->str, "<", 2) == 0)
		token->type = REDIN;
}

static void	handle_operator(char **loop, t_list **token, char buffer[BSIZE])
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

static int	process(char **loop, t_list **token, char *buffer, int *i)
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
	else if (check_operator(*loop))
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
