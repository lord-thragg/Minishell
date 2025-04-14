/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile_order.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 08:19:11 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/14 16:33:13 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	choose_infile_order(t_shell *shell, t_cmd *cmd)
{
	int value;
	
	value = 0;
	if (cmd->last)
	{
		if (cmd->infile)
			value = manage_infile(cmd->infile, cmd);
		dup2(shell->initin, 0);
		if (cmd->limiters[0])
			do_all_heredocs(cmd->limiters);
	}
	else
	{
		if (cmd->limiters[0])
			do_all_heredocs(cmd->limiters);
		if (cmd->infile)
			value = manage_infile(cmd->infile, cmd);
	}
	if (value == -1)
		return (value);
	return (0);
}
