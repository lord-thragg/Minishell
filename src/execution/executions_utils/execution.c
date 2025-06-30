/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:37:26 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/20 12:09:21 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_bultins(char *str, t_shell *shell)
{
	if (ft_strcmp(str, "unset") == 0)
	{
		ft_unset(shell, shell->cmd->cmd_list[1]);
		return (1);
	}
	if (ft_strcmp(str, "cd") == 0)
	{
		shell->ecode = cd(shell, shell->cmd->cmd_list[1]);
		return (1);
	}
	if (ft_strcmp(str, "exit") == 0)
	{
		shell->ecode = 0;
		ft_exit(shell);
		return (1);
	}
	return (0);
}

void	child_execution(t_cmd *cmd, t_shell *shell)
{
	char	*path;

	path = find_path(cmd->cmd_list[0], shell);
	if (!path)
	{
		path = ft_strjoin(cmd->cmd_list[0], ":command not found\n");
		ft_putstr_fd(path, 2);
		free(path);
		free_all(shell, NULL, -1);
		ft_freetab(shell->env);
		exit(EXT_COMMAND_NOT_FOUND);
	}
	if (execve(path, cmd->cmd_list, shell->env) == -1)
	{
		free(path);
		free_all(shell, NULL, 1);
	}
}

void	parent_management(int infile, int outfile)
{
	if (outfile > 1)
		close(outfile);
	if (dup2(infile, 0) == -1)
		perror("parent management: ");
	close(infile);
}

static int	check_bultin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->cmd_list[0], "echo") == 0)
	{
		echo(cmd->cmd_list);
		shell->ecode = 0;
		free_all(shell, NULL, shell->ecode);
	}
	else if (ft_strcmp(cmd->cmd_list[0], "export") == 0)
	{
		if (!shell->cmd->cmd_list[1])
			copy_and_display_sorted_env(shell->env);
		free_all(shell, NULL, shell->ecode);
	}
	else if (ft_strcmp(cmd->cmd_list[0], "env") == 0)
	{
		ft_env(shell);
		free_all(shell, NULL, shell->ecode);
	}
	else if (ft_strcmp(cmd->cmd_list[0], "cd") == 0)
		free_all(shell, NULL, shell->ecode);
	else if (ft_strcmp(cmd->cmd_list[0], "pwd") == 0)
	{
		ft_pwd(shell);
		free_all(shell, NULL, shell->ecode);
	}
	return (0);
}

void	simple_execution(t_cmd *cmd, t_shell *shell, int pipin, int pipout)
{
	singleton(2);
	g_sigpid = fork();
	if (g_sigpid == -1)
		perror("fork failed!\n");
	if (!g_sigpid)
	{
		signal_child();
		close(shell->initin);
		close(shell->initout);
		if (pipin > 0)
			close(pipin);
		if (pipout > 1)
		{
			dup2(pipout, 1);
			close(pipout);
		}
		if (!check_bultin(cmd, shell))
			child_execution(cmd, shell);
	}
	else
	{
		parent_management(pipin, pipout);
		shell->last_pid = g_sigpid;
	}
}
