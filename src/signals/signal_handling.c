/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:34:27 by luluzuri          #+#    #+#             */
/*   Updated: 2025/01/20 10:34:28 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int signum, siginfo_t *info, void *oldact)
{
	(void)oldact;
	(void)info;
	(void)signum;
	if (signum == SIGINT)
		printf("\n");
}

void	set_sigact(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa, NULL);
}
