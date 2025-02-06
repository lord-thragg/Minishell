/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:47:11 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/06 12:16:58 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_token(t_shell *shell, char **splitted)
{
	shell->token = (t_token *)malloc(sizeof(t_token));
	if (!shell->token)
		return (0);
	
}

int	parsing(t_shell *shell, char *input)
{
	char	**splitted;

	splitted = ft_split(input, ' ');
	if (!splitted)
		return (0);
	if (!create_token(shell, splitted))
		return (0);
	return (1);
}
