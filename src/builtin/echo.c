/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:08:34 by lle-duc           #+#    #+#             */
/*   Updated: 2025/02/27 16:54:51 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_freetab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (tab);
}

int	print_quoat(char *str, int *i, int pipefd)
{
	int	j;

	j = *i + 1;
	while (str[j])
	{
		if (str[j] == 39)
		{
			j = *i + 1;
			while (str[j] != 39)
			{
				write(pipefd, &str[j], 1);
				j++;
			}
			*i = j + 1;
			return (j);
		}
		j++;
	}
	return (0);
}

void	check_env(char *str, int pipefd, t_shell *shell)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			if (print_quoat(str, &i, pipefd) > 0)
				continue ;
		}
		else if (str[i] == '$' && str[i + 1])
		{
			if (ft_strcmp(str + i, "$?") == 0)
				ft_putnbr_fd(shell->ecode, pipefd);
			else
				ft_putstr_fd(ft_getenv(str + i + 1, shell), pipefd);
			break ;
		}
		else
			write(pipefd, &str[i], 1);
		i++;
	}
}

void	echo(char *options, t_shell *shell)
{
	int		i;
	char	**splited;

	if (!options)
		write(1, "\n", 1);
	splited = ft_split(options, ' ');
	i = 0;
	if (ft_strcmp(splited[0], "-n") == 0)
		i++;
	while (splited[i])
	{
		check_env(splited[i], 1, shell);
		if (splited[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (ft_strcmp(splited[0], "-n") != 0)
		write(1, "\n", 1);
	ft_freetab(splited);
	exit(0);
}
