/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_handle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:22:53 by lle-duc           #+#    #+#             */
/*   Updated: 2025/02/27 22:40:20 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc_loop(char *limiter, int pipefd)
{
	char	*line;

	while (1)
	{
		ft_putstr_fd("> ", 1);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			if (pipefd)
				close(pipefd);
			close(STDIN_FILENO);
			get_next_line(STDIN_FILENO);
			return ;
		}
		if (pipefd)
			ft_putstr_fd(line, pipefd);
		free(line);
	}
}

int     do_all_heredocs(char **heredocs)
{
    int i;
    int outfd[2];
	int defaultin;
	
	defaultin = dup(0);
    i = 0;
    while (heredocs[i])
    {
		if (heredocs[i + 1] == NULL)
		{
        	pipe(outfd);
			here_doc_loop(heredocs[i], outfd[1]);
		}
		else
			here_doc_loop(heredocs[i], 0);
		dup2(defaultin, 0);
        i++;
    }
	dup2(defaultin, 0);
	close(defaultin);
	if (dup2(outfd[0], 0) == -1)
		perror("dup2 failed, undefined results!\n");
	close(outfd[0]);
	return (outfd[0]);
}
