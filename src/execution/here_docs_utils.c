/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_docs_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 13:13:58 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/09 10:11:52 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*check_remainder(char **remainder)
{
	int		pos;
	char	*line;
	char	*temp;

	pos = -1;
	if (*remainder)
	{
		while ((*remainder)[++pos] != '\0')
		{
			if ((*remainder)[pos] == '\n')
				break ;
		}
		if ((*remainder)[pos] == '\n')
		{
			line = ft_substr(*remainder, 0, pos + 1);
			temp = ft_substr(*remainder, pos + 1, ft_strlen(*remainder));
			free(*remainder);
			*remainder = temp;
			return (line);
		}
	}
	return (NULL);
}

static int	read_from_fd(int fd, char **buffer)
{
	int	bytes_read;

	*buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!*buffer)
		return (-1);
	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (-1);
	}
	(*buffer)[bytes_read] = '\0';
	return (bytes_read);
}

static int	read_and_update(int fd, char **remainder)
{
	char	*buffer;
	int		bytes_read;
	char	*temp;

	bytes_read = read_from_fd(fd, &buffer);
	if (bytes_read == -1)
	{
		free(*remainder);
		*remainder = NULL;
		return (-1);
	}
	if (!*remainder)
		*remainder = ft_strdup(buffer);
	else
	{
		temp = ft_strjoin(*remainder, buffer);
		free(*remainder);
		*remainder = temp;
	}
	free(buffer);
	if (bytes_read == 0)
		return (0);
	return (1);
}

static char	*file_end(char **remainder)
{
	char	*line;

	if (*remainder && **remainder)
	{
		line = ft_strdup(*remainder);
		free(*remainder);
		*remainder = NULL;
		return (line);
	}
	free(*remainder);
	*remainder = NULL;
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*remainder[1024];
	char		*line;
	int			bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	while (1)
	{
		line = check_remainder(&remainder[fd]);
		if (line)
			return (line);
		bytes_read = read_and_update(fd, &remainder[fd]);
		if (bytes_read == -1)
			return (NULL);
		if (bytes_read == 0)
			break ;
	}
	return (file_end(&remainder[fd]));
}
