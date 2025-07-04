/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 15:07:45 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/01 16:47:29 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_envpath(char *env_variable, char **env)
{
	char	*path;
	char	**split;
	int		i;

	path = NULL;
	i = 0;
	while (env[i])
	{
		split = ft_split(env[i], '=');
		if (ft_strcmp(split[0], env_variable) == 0)
		{
			path = env[i] + ft_strlen(env_variable) + 1;
			ft_freetab(split);
			break ;
		}
		ft_freetab(split);
		i++;
	}
	return (path);
}

static int	find_path_pos(char *env_variable, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], env_variable, ft_strlen(env_variable)) == 0)
		{
			return (i);
		}
		i++;
	}
	return (-1);
}

char	*ft_getenv(char *env_variable, t_shell *shell)
{
	return (find_envpath(env_variable, shell->env));
}

int	ft_getenv_pos(char *env_variable, t_shell *shell)
{
	return (find_path_pos(env_variable, shell->env));
}
