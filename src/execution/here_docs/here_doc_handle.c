/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:22:53 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/14 16:26:24 by lle-duc          ###   ########.fr       */
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

void	do_all_heredocs(char **heredocs)
{
	pid_t pid;
	int	i;
	int	outfd[2];

	i = 0;
	singleton(2);
	pid = fork();
	if (pid == 0)
	{
		signal_heredoc();
		while (heredocs[i])
		{
			if (heredocs[i + 1] == NULL)
			{
				pipe(outfd);
				here_doc_loop(heredocs[i], outfd[1]);
				close(STDIN_FILENO);
				get_next_line(STDIN_FILENO);
				close(outfd[1]);
				dup2(outfd[0], 0);
			}
			else
				here_doc_loop(heredocs[i], 0);
			i++;
		}
		exit(0);
	}
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
