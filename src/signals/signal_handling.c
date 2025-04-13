/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:34:27 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/13 19:12:09 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Test singleton
/*void	*singleton(void *target)
{
	static void	*to_keep;

	if (target)
		to_keep = target;
	return (to_keep);
}*/
void	signal_child(void)
{
	(signal(SIGQUIT, SIG_DFL), signal(SIGINT, SIG_DFL));
}

void	signal_handler(int code)
{
	(void)code;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (g_sigpid == 130)
		rl_redisplay();
	if (g_sigpid == 0)
		rl_redisplay();
	g_sigpid = 130;
}

void	set_sigact(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
