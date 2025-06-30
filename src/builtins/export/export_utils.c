/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:23:47 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/03 11:43:45 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_sorted_env(char **env)
{
	int		i;
	int		j;
	char	*tmp;

	i = -1;
	j = 0;
	while (env[++i])
	{
		j = i;
		while (env[j])
		{
			if (env[j + 1] == NULL)
				break ;
			if (strcmp(env[i], env[j + 1]) > 0)
			{
				tmp = env[i];
				env[i] = env[j + 1];
				env[j + 1] = tmp;
			}
			j++;
		}
	}
	i = -1;
	while (env[++i])
		printf("export %s\n", env[i]);
}

void	copy_and_display_sorted_env(char **env)
{
	char	**copied_tab;

	copied_tab = copy_double_tab(env);
	print_sorted_env(copied_tab);
	ft_freetab(copied_tab);
}

void	change_env_value(t_shell *shell, char *env, char *new_value)
{
	env = recover_full_env(shell->env[ft_getenv_pos(env, shell)], new_value);
	if (env)
		export_all_env(env, shell);
	free(env);
}
