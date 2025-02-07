/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:35:26 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/07 16:40:34 by luluzuri         ###   ########.fr       */
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


