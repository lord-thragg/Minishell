/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:54:13 by lle-duc           #+#    #+#             */
/*   Updated: 2025/02/27 23:02:01 by lle-duc          ###   ########.fr       */
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
	if (shell->cmd->infile[0] != NULL || shell->cmd->limiters[0] != NULL)
	{
		close(pipefd[0]);
		if (shell->cmd->infile)
			manage_infile(shell->cmd->infile, pipefd, shell->cmd->cmd_list[0]);
		if (shell->cmd->limiters)
			pipefd[0] = do_all_heredocs(shell->cmd->limiters);
	}
	if (!shell->cmd->next)
	{
		close(pipefd[1]);
		pipefd[1] = 1;
	}
	if (shell->cmd->outfile[0] != NULL)
	{
		close(pipefd[1]);
		pipefd[1] = manage_outfile(shell->cmd->outfile, shell->cmd->append);
	}
	return (0);
}

static void	loop_execution(t_shell *shell, int *pipefd)
{
	while ((shell->cmd && shell->cmd->cmd_list[0]))
	{
		pipe(pipefd);
		if (manage_pipe_fd(shell, pipefd) == -1)
		{
			perror("Something went, output is undefined!\n");
			return ;
		}
		simple_execution(shell->cmd, shell, pipefd[0], pipefd[1]);
		shell->cmd = shell->cmd->next;
	}
}

void	execute_cmd(t_shell *shell)
{
	int	pipefd[2];
	int	initfdin;
	int	initfdout;

	if (shell->cmd->cmd_list[0])
	{
		if (ft_strcmp(shell->cmd->cmd_list[0], "export") == 0)
		{
			if (shell->cmd->next == NULL)
				export(shell, shell->cmd->cmd_list[1]);
			return ;
		}
		if (ft_strcmp(shell->cmd->cmd_list[0], "cd") == 0)
		{
			if (shell->cmd->next == NULL)
				cd(shell, shell->cmd->cmd_list[1]);
			return ;
		}
	}
	initfdin = dup(0);
	initfdout = dup(0);
	loop_execution(shell, pipefd);
	wait_all_pid(shell, initfdin, initfdout);
}
