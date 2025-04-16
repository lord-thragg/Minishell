/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:22:53 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/16 11:45:10 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_loop(char *limiter, int pipefd)
{
	char	*line;
	char	**split;

	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(STDIN_FILENO);
		split = ft_split(line, '\n');
		if (split && split[0] && ft_strcmp(split[0], limiter) == 0)
		{
			free(line);
			ft_freetab(split);
			return ;
		}
		if (split)
			ft_freetab(split);
		if (pipefd)
			ft_putstr_fd(line, pipefd);
		free(line);
	}
}

void	parent_heredoc(int outfd[2], pid_t pid)
{
	waitpid(pid, NULL, 0);
	close(outfd[1]);
	dup2(outfd[0], 0);
	close(outfd[0]);
}

void	child_heredoc(int outfd[2], char **heredocs)
{
	int	i;

	i = 0;
	while (heredocs[i])
	{
		if (heredocs[i + 1] == NULL)
		{
			here_doc_loop(heredocs[i], outfd[1]);
			close(STDIN_FILENO);
			get_next_line(STDIN_FILENO);
		}
		else
			here_doc_loop(heredocs[i], 0);
		i++;
	}
}

void	do_all_heredocs(char **heredocs, t_shell *shell, int *pipefd)
{
	pid_t	pid;
	int		outfd[2];

	singleton(2);
	pipe(outfd);
	pid = fork();
	if (pid == 0)
	{
		close(pipefd[0]);
		close(pipefd[1]);
		close(shell->initin);
		close(shell->initout);
		signal_heredoc();
		close(outfd[0]);
		child_heredoc(outfd, heredocs);
		close(outfd[1]);
		free_all(shell, NULL, 0);
	}
	else
		parent_heredoc(outfd, pid);
}

int	check_is_relative_path(char *program)
{
	char	**splited;
	int		i;

	splited = ft_split(program, '/');
	i = 0;
	if (splited)
	{
		while (splited[i])
			i++;
		if (i > 1 && splited[i - 1] && i > 1)
		{
			ft_freetab(splited);
			return (1);
		}
	}
	ft_freetab(splited);
	return (0);
}
