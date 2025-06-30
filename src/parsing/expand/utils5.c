/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 15:14:34 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/20 11:51:22 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	merge_joined_tokens(t_list **token_list)
{
	t_list	*current;
	t_list	*next;
	t_token	*curr_tok;
	t_token	*next_tok;
	char	*joined;

	current = *token_list;
	while (current && current->next)
	{
		curr_tok = (t_token *)current->content;
		next = current->next;
		next_tok = (t_token *)next->content;
		if (curr_tok->eindex == next_tok->sindex)
		{
			joined = ft_strjoin(curr_tok->str, next_tok->str);
			free(curr_tok->str);
			curr_tok->str = joined;
			curr_tok->eindex = next_tok->eindex;
			current->next = next->next;
			(free(next_tok->str), free(next_tok), free(next));
		}
		else
			current = current->next;
	}
}

void	*singleton_input(void *data)
{
	static void	*save;

	if (data)
		save = data;
	return (save);
}
