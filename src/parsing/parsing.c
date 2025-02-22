/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 13:18:50 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/22 13:19:08 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_token(t_token *ltoken)
{
	t_token	*tmp;

	tmp = ltoken;
	while (tmp)
	{
		printf("str: %s\ttype: %d\n", tmp->str, tmp->type);
		tmp = tmp->next;
	}
}

int	parsing(t_shell *shell, char *input)
{
	char	**splitted;

	splitted = ft_split(input, ' ');
	if (!splitted)
		return (0);
	shell->token = tokenize(splitted);
	if (!shell->token)
		return (0);
	print_token(shell->token);
	shell->cmd = token_to_command(shell->token);
	if (!shell->cmd)
		return (0);
	shell->token = NULL;
	return (1);
}
