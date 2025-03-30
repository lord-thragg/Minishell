/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:11:34 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/30 14:44:54 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_things(void)
{
	printf("Ici tout a ete free\n");
	return ;
}

int	parsing(t_shell *shell, t_list *token, char *input)
{
	if (ft_strlen(input) > 0 && tokenize(&token, input) != KO)
		return (free_things(), KO);
	return (OK);
}
