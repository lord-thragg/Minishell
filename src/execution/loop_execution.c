/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:54:13 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/09 08:37:35 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_all_pid(t_shell *shell, int in, int out)
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
	dup2(in, 0);
	dup2(out, 1);
	close(in);
	close(out);
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
		close(pipefd[0]);
		if (shell->cmd->infile)
			pipefd[0] = manage_infile(shell->cmd->infile, pipefd, shell->cmd);
		if (shell->cmd->limiters[0])
			do_all_heredocs(shell->cmd->limiters);
		return (1);
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
	int		initfdin;
	int		initfdout;
	t_shell	*tmp;

	tmp = shell;
	if (tmp->cmd->cmd_list[0] && tmp->cmd->next == NULL)
	{
		if (execute_bultins(tmp->cmd->cmd_list[0], tmp))
			return ;
	}
	initfdin = dup(0);
	initfdout = dup(1);
	loop_execution(tmp, pipefd);
	wait_all_pid(tmp, initfdin, initfdout);
}
