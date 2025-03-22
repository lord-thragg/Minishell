/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:31:19 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/17 12:25:10 by lle-duc          ###   ########.fr       */
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
	nenv[0] = ft_strdup("PATH=/usr/bin");
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

int	manage_parsing_output(t_shell *shell, char *input)
{
	int	ret;

	ret = parsing(shell, input);
	if (!ret)
	{
		free_all(shell, ER_PARSING, -1);
		return (1);
	}
	else if (ret == 2)
		return (1);
	add_history(input);
	execute_cmd(shell);
	free_all(shell, NULL, -1);
	return (0);
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
		if (g_sigpid == 130)
		{
			g_sigpid = 0;
			shell.ecode = 130;
		}
		if (!input)
			(free(input), free_all(&shell, "exit\n", 0));
		if (input && *input)
		{
			if (manage_parsing_output(&shell, input))
				continue ;
		}
	}
	rl_clear_history();
	return (0);
}
