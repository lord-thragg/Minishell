/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:31:19 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/26 17:16:43 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t		g_sigpid;

static char	**copy_double_tab(char **env)
{
	int		i;
	char	**newtab;

	i = 0;
	while (env[i])
		i++;
	newtab = malloc(sizeof(char *) * (i + 1));
	if (!newtab)
	{
		perror("malloc failed in copytab");
		return (NULL);
	}
	newtab[i] = NULL;
	i = 0;
	while (env[i])
	{
		newtab[i] = ft_strdup(env[i]);
		i++;
	}
	return (newtab);
}

static int	init_env(t_shell *shell, char **env)
{
	char	**nenv;

	if (env && env[0])
	{
		shell->env = copy_double_tab(env);
		return (1);
	}
	nenv = (char **)malloc(2 * sizeof(char *));
	if (!nenv)
		return (0);
	nenv[0] = strdup("PATH=/usr/bin");
	nenv[1] = NULL;
	shell->env = nenv;
	return (1);
}

static int	init_shell(t_shell *shell, char **env)
{
	set_sigact();
	shell->token = NULL;
	shell->cmd = NULL;
	shell->ecode = 0;
	g_sigpid = 0;
	if (!init_env(shell, env))
		return (0);
	return (1);
}

int	minishell(char **env)
{
	t_shell	shell;
	char	*input;

	if (!init_shell(&shell, env))
		free_all(&shell, ER_SHELL, EXT_SHELL);
	while (1)
	{
		input = readline("\033[0;32mminishell\033[0m-> ");
		if (!input || strcmp(input, "exit") == 0)
		{
			free(input);
			break ;
		}
		if (input && *input)
		{
			if (!parsing(&shell, input))
				free_all(&shell, ER_PARSING, EXT_PARSING);
			add_history(input);
			execute_cmd(&shell);
			free_all(&shell, NULL, -1);
		}
		g_sigpid = 0;
	}
	rl_clear_history();
	return (0);
}
