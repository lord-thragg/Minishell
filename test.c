/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 15:24:53 by luluzuri          #+#    #+#             */
/*   Updated: 2025/01/29 15:31:03 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// Gestionnaire pour SIGINT (Ctrl+C)
void	handle_sigint(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

int	main(void)
{
	struct sigaction	sa;
	char				*input;

	sa.sa_handler = handle_sigint; // Définit la fonction de gestion du signal
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;     // Redémarre readline après interruption
	sigaction(SIGINT, &sa, NULL); // Applique le handler pour SIGINT
	while (1)
	{
		input = readline("> "); // Affiche le prompt et attend une entrée
		if (!input)
		{ // Si Ctrl+D ou EOF, readline retourne NULL
			printf("\nBye!\n");
			break ;
		}
		if (*input)
		{ // Ajoute la commande à l'historique si elle n'est pas vide
			add_history(input);
		}
		printf("Commande entrée: %s\n", input);
		free(input); // Libérer la mémoire allouée par readline
	}
	return (0);
}
