/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:22:53 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/20 12:35:18 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_loop(char *limiter, int pipefd, t_shell *shell)
{
	char	*line;
	char	*expanded;
	char	**split;

	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			return (ft_putstr_fd(ER_HEREDOC, 2), ft_putstr_fd(limiter, 2),
				write(2, "')\n", 3),
				close(pipefd), free_all(shell, 0, 1));
		split = ft_split(line, '\n');
		if (split && split[0] && ft_strcmp(split[0], limiter) == 0)
		{
			free(line);
			ft_freetab(split);
			return ;
		}
		ft_freetab(split);
		expanded = expand_line(line, shell);
		ft_putstr_fd(expanded, pipefd);
		free(expanded);
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

void	child_heredoc(int outfd[2], char **heredocs, t_shell *shell)
{
	int	i;

	i = 0;
	singleton_shell(shell);
	while (heredocs[i])
	{
		if (heredocs[i + 1] == NULL)
		{
			here_doc_loop(heredocs[i], outfd[1], shell);
			close(STDIN_FILENO);
			get_next_line(STDIN_FILENO);
		}
		else
			here_doc_loop(heredocs[i], 0, shell);
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
		child_heredoc(outfd, heredocs, shell);
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
