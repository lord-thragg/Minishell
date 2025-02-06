/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:47:11 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/06 12:27:48 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_token(t_shell *shell, char **splitted)
{
	t_token	*token;
	int		i;

	i = 0;
	token = shell->token;
	if (!token)
		return (0);
	// need to initialize the token ( malloc )
	// and figure out how to give a type to a token
	// i'll need to do this for every single str in splitted
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
