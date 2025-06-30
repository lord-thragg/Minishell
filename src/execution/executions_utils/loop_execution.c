/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop_execution.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:54:13 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/19 17:19:19 by lle-duc          ###   ########.fr       */
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
			if (WIFSIGNALED(status) && WTERMSIG(status) == 3)
			{
				ft_strsignal(WTERMSIG(status));
				shell->ecode = 131;
			}
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
		if (choose_infile_order(shell, cmd, pipefd) == -1)
		{
			shell->last_pid = 1;
			return (1);
		}
	}
	return (0);
}

static void	loop_execution(t_shell *shell, int *pipefd)
{
	t_cmd	*tmp;
	int		code;

	tmp = shell->cmd;
	while (((tmp && tmp->cmd_list[0]) || (tmp && tmp->limiters[0])))
	{
		singleton(1);
		pipe(pipefd);
		code = manage_pipe_fd(shell, tmp, pipefd);
		if (tmp && tmp->cmd_list[0])
		{
			if (pipefd[0] >= 0 && pipefd[1] >= 1 && code == 0)
				simple_execution(tmp, shell, pipefd[0], pipefd[1]);
			if (code)
				close(pipefd[0]);
			tmp = tmp->next;
		}
		else
		{
			if (tmp->limiters[0])
				break ;
		}
	}
}

static void	create_all_outfiles(t_shell *shell)
{
	int		i;
	int		pipefd;
	t_cmd	*tmp;

	tmp = shell->cmd;
	i = 0;
	while (tmp)
	{
		while (tmp->outfile[i])
		{
			unlink(tmp->outfile[i]);
			pipefd = open(tmp->outfile[i], O_RDWR | O_APPEND | O_CREAT,
					00400 | 00200);
			close(pipefd);
			i++;
		}
		tmp = tmp->next;
	}
}

void	execute_cmd(t_shell *shell)
{
	int		pipefd[2];
	t_cmd	*head;

	create_all_outfiles(shell);
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
