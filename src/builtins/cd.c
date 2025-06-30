/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 07:49:26 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/19 13:34:44 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_pwd(t_shell *shell, char *path, int oldpwd)
{
	char	cwd[4096];
	char	*pwd;

	if (getcwd(cwd, 4096) == NULL)
	{
		perror(path);
		return (1);
	}
	if (oldpwd)
		pwd = ft_strjoin("OLDPWD=", path);
	else
		pwd = ft_strjoin("PWD=", cwd);
	if (!pwd)
		return (1);
	export_all_env(pwd, shell);
	free(pwd);
	return (0);
}

int	check_home(t_shell *shell)
{
	char	*env;
	char	oldpwd[4096];
	int		ret;

	getcwd(oldpwd, 4096);
	env = ft_getenv("HOME", shell);
	if (!env)
		return (printf("cd: HOME not set\n"), 1);
	ret = chdir(env);
	if (ret == 0)
	{
		update_pwd(shell, env, 0);
		update_pwd(shell, oldpwd, 1);
		return (ret);
	}
	return (1);
}

int	cd(t_shell *shell, char *path)
{
	int		ret;
	char	oldpwd[4096];

	getcwd(oldpwd, 4096);
	if (path)
	{
		ret = chdir(path);
		if (ret == 0)
		{
			update_pwd(shell, path, 0);
			update_pwd(shell, oldpwd, 1);
		}
		if (ret != 0)
		{
			perror(path);
			return (1);
		}
		return (0);
	}
	return (check_home(shell));
}

// int	main(int argc, char **argv)
// {
// 	if (argc < 2)
// 	{
// 		printf("Usage: %s path\n", argv[0]);
// 		exit(EXIT_FAILURE);
// 	}
// 	if (cd(argv[1]) != 0)
// 	{
// 		perror("Echec de la commande cd");
// 		exit(EXIT_FAILURE);
// 	}
// 	return (0);
// }
