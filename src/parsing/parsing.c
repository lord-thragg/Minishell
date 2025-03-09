/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:18:50 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/09 09:45:51 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parsing(t_shell *shell, char *input)
{
	char	**splitted;

	splitted = ft_splitspace(input);
	if (!splitted)
		return (0);
	shell->token = tokenize(splitted);
	if (!shell->token)
		return (0);
	shell->cmd = token_to_command(shell->token);
	if (!shell->cmd)
		return (0);
	return (1);
}
