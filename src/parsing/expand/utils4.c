/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:22:52 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/20 09:45:45 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*the_join(char *str, char *backup, char *buffer)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (backup[++i])
		str[i] = backup[i];
	while (buffer[j])
		str[i++] = buffer[j++];
	str[i] = '\0';
	return (str);
}

char	*strjoin_free(char *backup, char *buffer)
{
	char	*str;

	if (!backup)
	{
		backup = malloc(1 * sizeof(char));
		backup[0] = '\0';
	}
	if (!backup || !buffer)
	{
		if (backup)
			free(backup);
		return (0);
	}
	str = malloc(sizeof(char) * ((ft_strlen(backup) + ft_strlen(buffer)) + 1));
	if (!str)
	{
		if (backup)
			free(backup);
		return (0);
	}
	str = the_join(str, backup, buffer);
	free(backup);
	return (str);
}

int	condition_for_expand(t_list *token, char *str)
{
	if ((((t_token *)token->content)->quote != SQUOTE) && (!str || (str
				&& ft_strncmp(str, "<<", 2) != 0)))
		return (OK);
	return (KO);
}

int	get_pid_from_proc(void)
{
	int		fd;
	char	buf[1024];
	char	*pid_line;
	int		pid;

	ft_bzero(buf, 1024);
	fd = open("/proc/self/status", O_RDONLY);
	if (fd < 0)
		return (-1);
	read(fd, buf, sizeof(buf) - 1);
	close(fd);
	pid_line = strstr(buf, "Pid:\t");
	if (!pid_line)
		return (-1);
	pid = -1;
	sscanf(pid_line, "Pid:\t%d", &pid);
	return (pid);
}

void	expand_pid(char **str)
{
	free(*str);
	*str = ft_itoa(get_pid_from_proc());
}
