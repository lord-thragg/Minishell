/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:34:27 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/19 15:17:36 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	signal_handler(int code)
{
	(void)code;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (singleton(0) == 1)
		rl_redisplay();
	g_sigpid = 130;
}

void	set_sigact(void)
{
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

char	*ft_strsignal(int sig)
{
	int				i;
	static t_sigmsg	sigs[] = {{1, "Hangup"}, {2, "Interrupt"}, {3,
		"Quit (core dumped)"}, {6, "Aborted (core dumped)"}, {8,
		"Floating point exception (core dumped)"}, {9, "Killed"}, {11,
		"Segmentation fault (core dumped)"}, {13, "Broken pipe"}, {14,
		"Alarm clock"}, {15, "Terminated"}, {0, NULL}};

	i = 0;
	while (sigs[i].msg)
	{
		if (sigs[i].sig == sig)
			printf("%s\n", sigs[i].msg);
		i++;
	}
	return (NULL);
}
