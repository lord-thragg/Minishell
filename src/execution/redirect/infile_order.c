/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:19:11 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/12 13:35:25 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_infile_order(t_shell *shell, t_cmd *cmd)
{
	if (cmd->last)
	{
		if (cmd->infile)
			manage_infile(cmd->infile, cmd);
		dup2(shell->initin, 0);
		if (cmd->limiters[0])
			do_all_heredocs(cmd->limiters);
	}
	else
	{
		if (cmd->limiters[0])
			do_all_heredocs(cmd->limiters);
		if (cmd->infile)
			manage_infile(cmd->infile, cmd);
	}
}
