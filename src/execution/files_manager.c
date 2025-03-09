/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:18:45 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/09 08:46:36 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_directory(char *program, char **paths)
{
	struct stat statbuf;

	if (stat(program, &statbuf) != -1)
	{
		if (S_ISDIR(statbuf.st_mode)) 
		{
			ft_putstr_fd(program, 2);
			write(2, ": Is a directory\n", 17);
			ft_freetab(paths);
			exit(21);
		}
	}
}

static char	*try_access_program(char **paths, char *program)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		tmp = full_path;
		full_path = ft_strjoin(tmp, program);
		free(tmp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			return (full_path);
		}
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_path(char *program, t_shell *shell)
{
	char	**paths;
	char	*full_path;
	
	if (check_is_relative_path(program))
		return (program);
	paths = ft_split(ft_getenv("PATH", shell), ':');
	if (!paths)
		return (NULL);
	full_path = try_access_program(paths, program);
	if (!full_path)
	{
		ft_freetab(paths);
		paths = ft_split(ft_getenv("PWD", shell), ':');
		check_directory(program, paths);
	}
	full_path = try_access_program(paths, program);
	ft_freetab(paths);
	return (full_path);
}

int	manage_infile(char **files, int *pipefd, t_cmd *cmd)
{
	int i;
	char *cmd_name;

	i = -1;
	if (!cmd)
		cmd_name = NULL;
	else
		cmd_name = cmd->cmd_list[0];
	while (files[++i])
	{
		if (access(files[i], F_OK | R_OK) == -1)
		{
			perror(cmd_name);
		}
		pipefd[0] = open(files[i], O_RDONLY);
		if (pipefd[0] > 0)
		{
			dup2(pipefd[0], 0);
			close(pipefd[0]);
		}
		else
			return (-1);
	}
	return (pipefd[0]);
}

int	manage_outfile(char **files, int append)
{
	int	i;
	int pipefd;

	i = 0;
	pipefd = -1;
	while (files[i])
	{
		close(pipefd);
		if (!append)
		{
			unlink(files[i]);
			if (access(files[i], W_OK) >= 0 && access(files[i], W_OK) == -1)
				perror("Permission denied");
		}
		pipefd = open(files[i], O_RDWR | O_APPEND | O_CREAT, 00400 | 00200);
		i++;
	}
	return (pipefd);
}
