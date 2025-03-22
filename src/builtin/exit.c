/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 11:43:29 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/22 07:28:15 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell)
{
	if (shell->cmd->cmd_list[1])
		free_all(shell, NULL, ft_atoi(shell->cmd->cmd_list[1]));
	else
		free_all(shell, NULL, 0);
}
