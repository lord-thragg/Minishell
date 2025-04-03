/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 19:02:26 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/03 13:19:52 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Returns the last element of a linked list.
t_list	*ft_lstlast(t_list *lst)
{
	while (lst != NULL)
	{
		if (!lst->next)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}
