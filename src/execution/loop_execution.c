/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:54:13 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/22 12:14:04 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_all_pid(t_shell *shell)
{
	pid_t	wpid;
	int		status;

	wpid = wait(&status);
	while (wpid > 0)
	{
		if (wpid == shell->last_pid)
			shell->ecode = WEXITSTATUS(status);
		wpid = wait(&status);
	}
	dup2(shell->initin, 0);
	dup2(shell->initout, 1);
	close(shell->initin);
	close(shell->initout);
}

int	manage_pipe_fd(t_shell *shell, int *pipefd)
{
	if (!shell->cmd || !shell->cmd->next)
	{
		close(pipefd[1]);
		pipefd[1] = 1;
	}
	if (shell->cmd->outfile[0] != NULL)
	{
		close(pipefd[1]);
		pipefd[1] = manage_outfile(shell->cmd->outfile, shell->cmd->append);
	}
	if (shell->cmd->infile[0] != NULL || shell->cmd->limiters[0] != NULL)
	{
		choose_infile_order(shell);
	}
	return (0);
}

static void	loop_execution(t_shell *shell, int *pipefd)
{
	while (((shell->cmd && shell->cmd->cmd_list[0]) || (shell->cmd
				&& shell->cmd->limiters[0])))
	{
		pipe(pipefd);
		manage_pipe_fd(shell, pipefd);
		if (shell->cmd && shell->cmd->cmd_list[0])
		{
			if (pipefd[0] >= 0 && pipefd[1] >= 1)
				simple_execution(shell->cmd, shell, pipefd[0], pipefd[1]);
			shell->cmd = shell->cmd->next;
		}
		else
		{
			if (shell->cmd->limiters[0])
				break ;
		}
	}
}

void	execute_cmd(t_shell *shell)
{
	int		pipefd[2];
	t_cmd	*head;

	head = shell->cmd;
	if (shell->cmd->cmd_list[0] && shell->cmd->next == NULL)
	{
		if (execute_bultins(shell->cmd->cmd_list[0], shell))
			return ;
	}
	shell->initin = dup(0);
	shell->initout = dup(1);
	loop_execution(shell, pipefd);
	wait_all_pid(shell);
	shell->cmd = head;
}
