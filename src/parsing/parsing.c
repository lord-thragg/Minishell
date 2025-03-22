/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:18:50 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/18 07:45:15 by lle-duc          ###   ########.fr       */
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
		return (2);
	return (0);
}

int	parsing(t_shell *shell, char *input)
{
	char	**splitted;

	splitted = NULL;
	if (check_only_space(input))
		return (2);
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
