/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:22:53 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/09 10:12:12 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_loop(char *limiter, int pipefd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			close(STDIN_FILENO);
			get_next_line(STDIN_FILENO);
			return ;
		}
		if (pipefd)
			ft_putstr_fd(line, pipefd);
		free(line);
	}
}

void	do_all_heredocs(char **heredocs)
{
	int	i;
	int	outfd[2];

	i = 0;
	while (heredocs[i])
	{
		if (heredocs[i + 1] == NULL)
		{
			pipe(outfd);
			here_doc_loop(heredocs[i], outfd[1]);
			close(outfd[1]);
			dup2(outfd[0], 0);
			close(outfd[0]);
		}
		else
			here_doc_loop(heredocs[i], 0);
		i++;
	}
}

int	check_is_relative_path(char *program)
{
	char	**splited;
	int		i;

	splited = ft_split(program, '/');
	i = 0;
	while (splited[i])
		i++;
	if (splited[i - 1] && i > 1)
	{
		ft_freetab(splited);
		return (1);
	}
	ft_freetab(splited);
	return (0);
}

char	**ft_freetab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (tab);
}
