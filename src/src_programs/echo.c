/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:08:34 by lle-duc           #+#    #+#             */
/*   Updated: 2025/01/20 11:41:24 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo(int argc, char **av, int option)
{
	int	i;

	i = 1;
	i += (option == 1);
	while (i < argc)
	{
		write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
		i++;
		if (i < argc)
			write(1, " ", 1);
	}
	if (!option)
		write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	if (argc > 1)
		echo(argc, argv, ft_strcmp(argv[1], "-n") == 0);
	else
		write(1, "\n", 1);
}
