/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 14:18:45 by lle-duc           #+#    #+#             */
/*   Updated: 2025/02/27 22:18:04 by lle-duc          ###   ########.fr       */
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
		full_path = ft_strjoin(full_path, program);
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

void	manage_infile(char **files, int *pipefd, char *cmd)
{
	int i;

	i = -1;
	while (files[++i])
	{
		if (access(files[i], F_OK) == -1)
		{
			print_no_file_error(cmd, files[i], 0);
		}
		if (access(files[i], R_OK) == -1)
		{
			print_no_file_error(cmd, files[i], 1);
		}
		pipefd[0] = open(files[i], O_RDONLY);
		if (dup2(pipefd[0], 0) == -1)
			perror("dup2 failed, undefined results!");
		close(pipefd[0]);
	}
}

int	manage_outfile(char **files, int append)
{
	int	i;
	int pipefd;

	i = 0;
	pipefd = -1;
	while (files[i])
	{
		if (pipefd > 0)
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
