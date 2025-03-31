/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 17:11:47 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/31 15:48:14 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_t(t_list *token)
{
	t_list	*tmp;
	t_token	*content;

	tmp = token;
	while (tmp)
	{
		if (tmp->content)
		{
			content = tmp->content;
			if (content->str != NULL)
				printf("%s\n", content->str);
			else
				printf("(null)\n");
			if (content->type)
				printf("type -> %d\n", content->type);
		}
		else
			printf("(null content)\n");
		tmp = tmp->next;
	}
}

void	free_all(void)
{
	printf("Ici tout a ete free\n");
	return ;
}

t_list	*ft_lstnew_custom(char buffer[BSIZE])
{
	char		*the_buffer;
	t_token		*token;
	t_list		*new;

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