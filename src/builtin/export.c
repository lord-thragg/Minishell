/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:10:38 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/24 08:38:54 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**split_first(char *env)
{
	int		i;
	char	**splited;

	splited = malloc(sizeof(char *) * 3);
	if (!splited)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (env[i] == '=' && i > 1)
		{
			splited[0] = ft_substr(env, 0, i);
			splited[1] = ft_substr(env, i + 1, ft_strlen(env));
			splited[2] = NULL;
			if (!splited[0] || !splited[1])
			{
				ft_freetab(splited);
				return (NULL);
			}
			return (splited);
		}
		i++;
	}
	return (NULL);
}

static char	**append_export(char **tab, char *str)
{
	int		i;
	char	**newtab;

	i = 0;
	while (tab[i])
		i++;
	newtab = malloc(sizeof(char *) * (i + 2));
	if (!newtab)
	{
		perror("malloc failed in export\n");
		return (NULL);
	}
	i = 0;
	while (tab[i])
	{
		newtab[i] = ft_strdup(tab[i]);
		i++;
	}
	ft_freetab(tab);
	newtab[i] = ft_strdup(str);
	newtab[i + 1] = NULL;
	return (newtab);
}

static void	export_all_env(char *env, t_shell *shell)
{
	char	**splited;
	int		i;

	if (!env)
		return ;
	splited = split_first(env);
	if (!splited)
		return ;
	i = ft_getenv_pos(splited[0], shell);
	if (i >= 0)
	{
		free(shell->env[i]);
		shell->env[i] = ft_strdup(env);
	}
	else
	{
		shell->env = append_export(shell->env, env);
	}
	ft_freetab(splited);
	shell->ecode = 0;
}

static char	*recover_full_env(char *init_env, char *new_env_value)
{
	char	*new_env;
	char	*tmp2;
	char	**tmp;

	if (!new_env_value)
		return (NULL);
	tmp = ft_split(init_env, '=');
	tmp2 = tmp[0];
	new_env = ft_strjoin(tmp2, "=");
	tmp2 = new_env;
	new_env = ft_strjoin(tmp2, new_env_value);
	free(tmp2);
	ft_freetab(tmp);
	return (new_env);
}

void	export(t_shell *shell, int i)
{
	int		j;
	char	*env;

	j = 0;
	while (shell->cmd->cmd_list[i])
	{
		while (shell->cmd->cmd_list[i][j] != '=')
			j++;
		if (shell->cmd->cmd_list[i][j + 1] == '$')
		{
			env = recover_full_env(shell->cmd->cmd_list[i],
					ft_getenv(shell->cmd->cmd_list[i] + j + 2, shell));
			if (env)
				export_all_env(env, shell);
			else
			{
				env = recover_full_env(shell->cmd->cmd_list[i], "");
				shell->env = append_export(shell->env, env);
			}
			free(env);
		}
		else
			export_all_env(shell->cmd->cmd_list[i], shell);
		i++;
	}
}
