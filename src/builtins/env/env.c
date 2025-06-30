/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 11:57:00 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/19 11:50:52 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_shell *shell)
{
	int	i;
	int	j;
	int	equal_count;

	i = 0;
	while (shell->env[i])
	{
		j = 0;
		equal_count = 0;
		while (shell->env[i][j])
		{
			if ((shell->env[i][j] == '=' && !shell->env[i][j + 1]
					&& equal_count == 0) || !ft_strchr(shell->env[i], '='))
				break ;
			if (shell->env[i][j] == '=')
				equal_count++;
			j++;
			if (!shell->env[i][j])
				printf("%s\n", shell->env[i]);
		}
		i++;
	}
	shell->ecode = 0;
}
