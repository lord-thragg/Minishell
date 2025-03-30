/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:18:50 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/30 10:17:05 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_only_space(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] != '\n')
	{
		if (input[i] != ' ')
		{
			i = -1;
			break ;
		}
		i++;
	}
	if (i != -1)
		return (KO);
	return (OK);
}

int	parsing(t_shell *shell, char *input)
{
	if (check_only_space(input) == KO)
		return (KO);
	if (ft_strlen(input) > 0 && tokenize(input, &shell->token))
	shell->cmd = token_to_command(shell->token);
	if (!shell->cmd)
		return (KO);
	return (OK);
}
