/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:11:34 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/01 09:32:11 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	expand(t_shell *shell, t_list *token)
{
	
}

static int	parser_set(t_shell *shell, t_list *token, char *input)
{
	if (expand(shell, token) == KO)
		return (KO);
}

int	parsing(t_shell *shell, t_list *token, char *input)
{
	(void)shell;
	if (ft_strlen(input) > 0 && tokenize(&token, input) != KO)
		if (token)
			if (parser_set(shell, token, input) == OK)
				return (OK);
	ft_lstclear_custom(&token, free);
	free(input);
	return (KO);
}
