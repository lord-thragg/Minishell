/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:31:19 by luluzuri          #+#    #+#             */
/*   Updated: 2025/01/31 16:38:32 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	g_sigpid;

int	init_shell(t_shell *shell, char **env)
{
	
}

int	minishell(char **env)
{
	t_shell	shell;
	char	*input;

	(void)env;
	set_sigact();
	if (init_shell(&shell, env))
		free_all(&shell, ER_MALLOC);
	while (1)
	{
		input = readline("\033[0;32mminishell\033[0m-> ");
		if (input == NULL || strcmp(input, "exit") == 0)
		{
			free(input);
			input = NULL;
			break ;
		}
		if (*input)
			add_history(input);
		g_sigpid = 0;
	}
	rl_clear_history();
	return (0);
}
