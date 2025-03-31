/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:11:28 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/31 11:43:46 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quitout(t_shell **shell)
{
	(void)shell;
	printf("%sError%s: a probleme occurred.\n", \
		RED, RESET);
	if (shell)
		free_all();
}

static int	init_shell(t_shell **shell)
{
	*shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (KO);
	return (OK);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_shell	*shell;
	char	*input;

	while (1)
	{
		input = readline("\033[0;32mminishell\033[0m-> ");
		if (!input)
			return (KO);
		if (ft_strncmp("exit", input, 5) == 0)
			break ;
		if (init_shell(&shell) == KO)
			return (quitout(&shell), KO);
		if (parsing(shell, shell->token, input) == KO)
			return (quitout(&shell), KO);
		free(input);
	}
	return (0);
}
