/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:11:47 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/30 17:30:16 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_t(t_list *token)
{
	t_list	*tmp;

	tmp = token;
	while (tmp)
	{
		printf("%s\n", ((t_token *)tmp->content)->str);
		tmp = tmp->next;
	}
}

void	free_all(void)
{
	printf("Ici tout a ete free\n");
	return ;
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