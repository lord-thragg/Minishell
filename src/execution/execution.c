/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 16:37:26 by lle-duc           #+#    #+#             */
/*   Updated: 2025/02/27 22:35:48 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	child_execution(char *cmd, char *options, t_shell *shell)
{
	char	*path;
	char	**full_cmd;

	path = find_path(cmd, shell);
	if (!path)
	{
		path = ft_strjoin(cmd, ":command not found\n");
		ft_putstr_fd(path, 2);
		free(path);
		exit(EXT_COMMAND_NOT_FOUND);
	}
	full_cmd = malloc(sizeof(char *) * 3);
	if (!full_cmd)
	{
		free(path);
		exit(EXT_MALLOC);
	}
	full_cmd[0] = cmd;
	full_cmd[1] = options;
	full_cmd[2] = NULL;
	if (execve(path, full_cmd, shell->env) == -1)
	{
		free(path);
		ft_freetab(full_cmd);
	}
}

void	parent_management(int infile, int outfile)
{
	close(outfile);
	dup2(infile, 0);
	close(infile);
}

static int	check_bultin(t_cmd *cmd, t_shell *shell)
{
	if (ft_strcmp(cmd->cmd_list[0], "echo") == 0)
		return (echo(cmd->cmd_list[1], shell), 1);
	else if (ft_strcmp(cmd->cmd_list[0], "export") == 0)
		exit(0);
	else if (ft_strcmp(cmd->cmd_list[0], "env") == 0)
		return (ft_env(shell), 1);
	else if (ft_strcmp(cmd->cmd_list[0], "cd") == 0)
		exit(0);
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
		if (pipin > 0)
			close(pipin);
		if (pipout > 1)
		{
			if (dup2(pipout, 1) == -1)
				perror("dup2 failed2\n");
			close(pipout);
		}
		signal_child();
		if (!check_bultin(cmd, shell))
			child_execution(cmd->cmd_list[0], cmd->cmd_list[1], shell);
	}
	else
	{
		parent_management(pipin, pipout);
		shell->last_pid = pid;
	}
}
