/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:19:11 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/17 12:26:30 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_infile_order(t_shell *shell)
{
	if (shell->cmd->last)
	{
		if (shell->cmd->infile)
			manage_infile(shell->cmd->infile, shell->cmd);
		dup2(shell->initin, 0);
		if (shell->cmd->limiters[0])
			do_all_heredocs(shell->cmd->limiters);
	}
	else
	{
		if (shell->cmd->limiters[0])
			do_all_heredocs(shell->cmd->limiters);
		if (shell->cmd->infile)
			manage_infile(shell->cmd->infile, shell->cmd);
	}
}
