/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 17:10:38 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/27 17:24:32 by luluzuri         ###   ########.fr       */
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
		perror("malloc failed in exportn");
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

void	export(t_shell *shell, char *env)
{
	char	**splited;
	int		i;

	if (!env)
		return ;
	splited = split_first(env);
	if (!splited)
	{
		perror("Malloc Failed in export!\n");
		return ;
	}
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
}
