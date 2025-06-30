/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:31:19 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/19 14:51:37 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t		g_sigpid;

char	**copy_double_tab(char **env)
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
	char	pwd[1024];

	if (env && env[0])
	{
		shell->env = copy_double_tab(env);
		return (1);
	}
	nenv = (char **)malloc(4 * sizeof(char *));
	if (!nenv)
		return (0);
	getcwd(pwd, 1024);
	nenv[0] = ft_strdup(ft_strjoin("PWD=", pwd));
	nenv[1] = ft_strdup("SHLVL=1");
	nenv[2] = ft_strdup("OLDPWD=");
	nenv[3] = NULL;
	shell->env = nenv;
	return (1);
}

static int	init_shell(t_shell *shell, char **env)
{
	char	*new_value;

	set_sigact();
	shell->token = NULL;
	shell->cmd = NULL;
	shell->ecode = 0;
	g_sigpid = 0;
	if (!init_env(shell, env))
		return (0);
	new_value = ft_itoa(ft_atoi(ft_getenv("SHLVL", shell)) + 1);
	change_env_value(shell, "SHLVL", new_value);
	free(new_value);
	return (1);
}

int	manage_parsing_output(t_shell *shell, char *input)
{
	int	ret;

	add_history(input);
	ret = parsing(shell, shell->token, input);
	if (ret == KO)
	{
		free_all(shell, ER_PARSING, -1);
		return (1);
	}
	else if (ret == 2)
		return (1);
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
		singleton(1);
		input = readline(RED"minishell\033[0m-> ");
		if (g_sigpid == 130)
		{
			g_sigpid = 0;
			shell.ecode = 130;
		}
		if (!input)
			(free(input), free_all(&shell, "exit\n", 0));
		if (input && *input)
			if (singleton_input(input) && manage_parsing_output(&shell, input))
				continue ;
	}
	return (rl_clear_history(), 0);
}
