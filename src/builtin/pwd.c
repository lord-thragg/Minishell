/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 08:18:22 by luluzuri          #+#    #+#             */
/*   Updated: 2025/01/21 08:26:18 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//#include "minishell.h"

int	main(void)
{
	char	cwd[1024];

	printf("%s\n", getcwd(cwd, sizeof(cwd)));
}
