/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:43:29 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/24 10:17:54 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	if (shell->cmd->cmd_list[1])
		free_all(shell, "exit\n", ft_atoi(shell->cmd->cmd_list[1]));
	else
		free_all(shell, "exit\n", 0);
}
