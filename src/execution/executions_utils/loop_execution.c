/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:54:13 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/14 12:37:09 by lle-duc          ###   ########.fr       */
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
		{
			shell->ecode = WEXITSTATUS(status);
			if (WIFSIGNALED(status))
				ft_strsignal(WTERMSIG(status));
		}
		wpid = wait(&status);
	}
	dup2(shell->initin, 0);
	dup2(shell->initout, 1);
	close(shell->initin);
	close(shell->initout);
}

int	manage_pipe_fd(t_shell *shell, t_cmd *cmd, int *pipefd)
{
	if (!cmd || !cmd->next)
	{
		close(pipefd[1]);
		pipefd[1] = 1;
	}
	if (cmd->outfile[0] != NULL)
	{
		close(pipefd[1]);
		pipefd[1] = manage_outfile(cmd->outfile, cmd->append);
	}
	if (cmd->infile[0] != NULL || cmd->limiters[0] != NULL)
	{
		choose_infile_order(shell, cmd);
	}
	return (0);
}

static void	loop_execution(t_shell *shell, int *pipefd)
{
	t_cmd	*tmp;

	tmp = shell->cmd;
	while (((tmp && tmp->cmd_list[0]) || (tmp && tmp->limiters[0])))
	{
		pipe(pipefd);
		manage_pipe_fd(shell, tmp, pipefd);
		if (tmp && tmp->cmd_list[0])
		{
			if (pipefd[0] >= 0 && pipefd[1] >= 1)
				simple_execution(tmp, shell, pipefd[0], pipefd[1]);
			tmp = tmp->next;
		}
		else
		{
			if (tmp->limiters[0])
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
	g_sigpid = 130;
	shell->cmd = head;
}
