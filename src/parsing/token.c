/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:35:26 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/08 16:20:09 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str)
{
	t_token	*ntoken;

	ntoken = (t_token *)malloc(sizeof(t_token));
	if (!ntoken)
		return (NULL);
	ntoken->str = ft_strdup(str);
	if (!ntoken->str)
		return (NULL);
	ntoken->next = NULL;
	ntoken->prev = NULL;
	return (ntoken);
}

void	add_token(t_token **head, t_token *ntoken)
{
	t_token	*tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = ntoken;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ntoken;
	ntoken->prev = tmp;
}

int	detect_type(char *str)
{
	if (!ft_strcmp(str, "|"))
		return (PIPE);
	if (!ft_strcmp(str, ">"))
		return (REDOUT);
	if (!ft_strcmp(str, "<"))
		return (REDIN);
	if (!ft_strcmp(str, ">>"))
		return (APPEND);
	if (!ft_strcmp(str, "<<"))
		return (HEREDOC);
	return (ARG);
}
