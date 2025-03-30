/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:37:26 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/28 08:24:07 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_bultins(char *str, t_shell *shell)
{
	if (ft_strcmp(str, "export") == 0)
	{
		if (!shell->cmd->cmd_list[1])
			return (ft_env(shell), 1);
		export(shell, 1);
		return (1);
	}
	if (ft_strcmp(str, "unset") == 0)
	{
		ft_unset(shell, shell->cmd->cmd_list[1]);
		return (1);
	}
	if (ft_strcmp(str, "cd") == 0)
	{
		cd(shell, shell->cmd->cmd_list[1]);
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

void	child_execution(char *cmd, t_shell *shell)
{
	char	*path;

	path = find_path(cmd, shell);
	if (!path)
	{
		path = ft_strjoin(cmd, ":command not found\n");
		ft_putstr_fd(path, 2);
		free(path);
		free_all(shell, NULL, -1);
		ft_freetab(shell->env);
		exit(EXT_COMMAND_NOT_FOUND);
	}
	if (execve(path, shell->cmd->cmd_list, shell->env) == -1)
	{
		free(path);
		free_all(shell, NULL, -1);
		ft_freetab(shell->env);
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
		echo(cmd->cmd_list, shell);
		free_all(shell, NULL, shell->ecode);
	}
	else if (ft_strcmp(cmd->cmd_list[0], "export") == 0)
		free_all(shell, NULL, shell->ecode);
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
	int	pid;

	pid = fork();
	if (pid == -1)
		perror("fork failed!\n");
	if (!pid)
	{
		close(shell->initin);
		close(shell->initout);
		if (pipin > 0)
			close(pipin);
		if (pipout > 1)
		{
			dup2(pipout, 1);
			close(pipout);
		}
		signal_child();
		if (!check_bultin(cmd, shell))
			child_execution(cmd->cmd_list[0], shell);
	}
	else
	{
		parent_management(pipin, pipout);
		shell->last_pid = pid;
	}
}
