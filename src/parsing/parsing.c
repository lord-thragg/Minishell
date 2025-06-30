/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:11:34 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/20 10:18:55 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	printc(t_cmd *cmd)
{
	int	i;

	while (cmd)
	{
		printf("new command -> \n");
		i = -1;
		while (cmd->cmd_list[++i])
			printf("%s\n", cmd->cmd_list[i]);
		cmd = cmd->next;
	}
}

int	parsing(t_shell *shell, t_list *token, char *input)
{
	if (ft_strlen(input) > 0 && tokenize(&token, input) != KO)
	{
		if (token)
		{
			if (parser_set(shell, token, input) == KO)
				return (KO);
			shell->token = token;
			shell->cmd = token_to_command(shell->token);
			if (!shell->cmd)
				return (ft_lstclear_cust(&token, free), token = NULL, KO);
			ft_lstclear_cust(&shell->token, free);
			free(shell->token);
			shell->token = NULL;
			return (OK);
		}
	}
	return (KO);
}
