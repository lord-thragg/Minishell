/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 13:35:29 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/20 12:33:33 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	singleton(int target)
{
	static int	to_keep;

	if (target > 0)
		to_keep = target;
	return (to_keep);
}

t_shell	*singleton_shell(t_shell *shell)
{
	static t_shell	*to_keep;

	if (shell != NULL)
		to_keep = shell;
	return (to_keep);
}

static void	signal_handler_heredoc(int code)
{
	(void)code;
	printf("\n");
	free_all(singleton_shell(NULL), NULL, 130);
}

void	signal_heredoc(void)
{
	signal(SIGINT, &signal_handler_heredoc);
	signal(SIGQUIT, SIG_DFL);
}
