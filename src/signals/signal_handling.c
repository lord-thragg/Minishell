/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 09:34:27 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/14 12:43:47 by lle-duc          ###   ########.fr       */
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
