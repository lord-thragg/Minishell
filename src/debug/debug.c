/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:42:40 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/13 13:22:24 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	debug(int *fd, char *str)
{
	char	*new;
	char	*mshell;

	new = "\n\nNew programme launched: \n";
	mshell = "minishell -> ";
	if (fd == 0)
	{
		*fd = open("debug.log", O_CREAT | O_APPEND | O_RDWR, 0644);
		if (write(*fd, new, ft_strlen(new)) == -1)
			return (perror("Error writing to debug.log"), close(*fd), KO);
	}
	if (*fd == -1)
	{
		perror("Error opening debug.log");
		return (KO);
	}
	if (write(*fd, mshell, ft_strlen(mshell)) == -1)
		return (perror("Error writing to debug.log"), close(*fd), KO);
	if (write(*fd, str, ft_strlen(str)) == -1)
		return (perror("Error writing to debug.log"), close(*fd), KO);
	if (write(*fd, "\n\n", 2) == -1)
		return (perror("Error writing to debug.log"), close(*fd), KO);
	return (OK);
}
