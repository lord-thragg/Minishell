/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:11:28 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/30 17:27:23 by luluzuri         ###   ########.fr       */
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
	t_shell	*shell;
	char	*input;

	if (ac != 2)
	{
		printf("%sUsage%s: %s <bash_command_n_args>\n", \
			RED, RESET, av[0]);
		return (1);
	}
	input = ft_strdup(av[1]);
	if (!input)
		return (KO);
	if (init_shell(&shell) == KO)
		return (quitout(&shell), KO);
	if (parsing(shell, shell->token, input) == KO)
		return (quitout(&shell), KO);
	free(shell);
	free(input);
	return (0);
}
