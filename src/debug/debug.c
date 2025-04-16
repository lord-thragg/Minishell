/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 12:42:40 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/16 10:40:20 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*singleton_fd(void *data)
{
	static void	*save;

	if (data)
		save = data;
	return (save);
}

int	debug(int *fd, char *str, int debug)
{
	char	*new;

	if (!debug)
		return (OK);
	new = "\n\nNew programme launched:\n";
	if (*fd == 0)
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
	if (write(*fd, "minishell-> ", ft_strlen("minishell-> ")) == -1)
		return (perror("Error writing to debug.log"), close(*fd), KO);
	if (write(*fd, str, ft_strlen(str)) == -1)
		return (perror("Error writing to debug.log"), close(*fd), KO);
	if (write(*fd, "\n\n", 2) == -1)
		return (perror("Error writing to debug.log"), close(*fd), KO);
	return (OK);
}
