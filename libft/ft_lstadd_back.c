/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:06:20 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/03 12:25:57 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Adds a new element at the end of a linked list.
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*list;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	list = ft_lstlast(*lst);
	list->next = new;
}
