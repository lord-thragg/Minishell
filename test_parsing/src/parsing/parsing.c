/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:11:34 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/31 11:29:12 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_shell *shell, t_list *token, char *input)
{
	(void)shell;
	if (ft_strlen(input) > 0 && tokenize(&token, input) != KO)
		return (free_all(), OK);
	return (OK);
}
