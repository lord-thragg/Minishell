/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:11:47 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/19 11:39:14 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printt(t_list *token)
{
	t_token	*t;

	while (token)
	{
		t = (t_token *)token->content;
		printf("[%s] (%d -> %d)\n", t->str, t->sindex, t->eindex);
		token = token->next;
	}
}

t_list	*ft_lstnew_custom(char buffer[BSIZE])
{
	char	*the_buffer;
	t_token	*token;
	t_list	*new;

	the_buffer = ft_strdup(buffer);
	token = ft_calloc(1, sizeof(t_token));
	if (!the_buffer || !token)
		return (NULL);
	token->str = the_buffer;
	new = ft_lstnew(token);
	if (!new)
	{
		free(the_buffer);
		free(token);
	}
	return (new);
}

void	ft_lstclear_cust(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;
	t_token	*token;

	tmp = *lst;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		del(token->str);
		tmp = tmp->next;
	}
	ft_lstclear(lst, del);
	free(*lst);
}

void	put_null(char **tab, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		tab[i] = NULL;
}
