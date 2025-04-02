/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 12:11:28 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/02 16:08:06 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quitout(t_shell *shell)
{
	(void)shell;
	printf("%sError%s: a probleme occurred.\n", \
		RED, RESET);
	if (shell)
		free_all();
}

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
	shell->token = NULL;
	shell->cmd = NULL;
	shell->ecode = 0;
	if (!init_env(shell, env))
		return (KO);
	return (OK);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_shell	shell;
	char	*input;

	printf("\n%s%s%s\n\n", CYAN, env[0], RESET);
	while (1)
	{
		input = readline("\033[0;32mminishell\033[0m-> ");
		if (!input)
			return (KO);
		if (ft_strncmp("exit", input, 5) == 0)
			break ;
		if (init_shell(&shell, env) == KO)
			return (quitout(&shell), KO);
		if (parsing(&shell, (&shell)->token, input) == KO)
			return (quitout(&shell), KO);
		free(input);
	}
	return (0);
}
