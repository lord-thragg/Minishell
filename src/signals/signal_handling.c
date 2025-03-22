/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:34:27 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/18 08:01:04 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_child(void)
{
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handler(int code)
{
	(void)code;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_sigpid == 0)
		rl_redisplay();
	g_sigpid = 130;
}

void	set_sigact(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
