/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 07:49:26 by luluzuri          #+#    #+#             */
/*   Updated: 2025/01/22 22:02:11 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include "minishell.h"

int	cd(char *path)
{
	if (chdir(path) != 0)
	{
		perror("chdir");
		return (-1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("Usage: %s path\n", argv[0]);
		exit(EXIT_FAILURE);
	}
	if (cd(argv[1]) != 0)
	{
		perror("Echec de la commande cd");
		exit(EXIT_FAILURE);
	}
	return (0);
}
