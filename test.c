/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:16:19 by luluzuri          #+#    #+#             */
/*   Updated: 2025/01/28 18:52:02 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "libft/libft.h"

int	main(int ac, char **av, char **env)
{
	char	*home;
	char	**path;
	int		i;

	(void)ac;
	(void)av;
	(void)env;
	i = 0;
	// Récupérer la valeur de la variable d'environnement "HOME"
	home = getenv("PATH");
	path = ft_split(home, ':');
	while (path[i])
	{
		printf("%s\n", path[i]);
		i++;
	}
	return (0);
}
