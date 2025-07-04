/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:30:33 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/20 11:53:55 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_token(t_list **token, char buffer[BSIZE], char *brut)
{
	t_list		*last;
	char		*raw_input;
	char		*tmp;
	size_t		start_index;
	static int	last_eindex = 0;

	raw_input = (char *)singleton_input(NULL);
	tmp = brut - ft_strlen(buffer);
	start_index = last_eindex;
	if (*token == NULL)
		*token = ft_lstnew_custom(buffer);
	else
		ft_lstadd_back(token, ft_lstnew_custom(buffer));
	last = ft_lstlast(*token);
	if (((t_token *)last->content)->type == 0)
		((t_token *)last->content)->type = ARG;
	((t_token *)last->content)->sindex = start_index;
	((t_token *)last->content)->eindex = (ft_strlen(raw_input)
			- ft_strlen(brut));
	if (raw_input[ft_strlen(raw_input) - ft_strlen(brut)] == ' ')
		((t_token *)last->content)->eindex += 1;
	last_eindex = (ft_strlen(raw_input) - ft_strlen(brut));
}

int	check_quote_type(char **loop)
{
	if (**loop == 34)
		return (DQUOTE);
	else if (**loop == 39)
		return (SQUOTE);
	return (0);
}

int	handle_quotes(char **loop, t_list **token, char buffer[BSIZE])
{
	int		quote;
	t_list	*last;
	t_token	*content;

	if (ft_strlen(buffer) > 0)
	{
		add_token(token, buffer, *loop);
		ft_bzero(buffer, BSIZE);
	}
	if (twin_quote(*loop) == OK)
	{
		quote = check_quote_type(loop);
		buffer = copy_to_twin(loop, buffer);
		add_token(token, buffer, *loop);
		last = ft_lstlast(*token);
		content = last->content;
		content->quote = quote;
		ft_bzero(buffer, BSIZE);
	}
	else
		return (ft_putstr_fd("Error: bad quotes.\n", 2), KO);
	return (OK);
}

void	increments(char **prompt_loop, char *buffer, int *i)
{
	buffer[*i] = **prompt_loop;
	(*i)++;
	(*prompt_loop)++;
}

int	check_operator(char *loop)
{
	if (ft_strncmp(loop, ">", 1) == 0)
		return (OK);
	if (ft_strncmp(loop, "<", 1) == 0)
		return (OK);
	if (ft_strncmp(loop, "|", 1) == 0)
		return (OK);
	return (KO);
}
