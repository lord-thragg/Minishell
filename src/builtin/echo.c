/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:08:34 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/09 10:50:20 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	char	*tmp;

	i = -1;
	while (str[++i])
	{
		if (str[i] == 39)
			if (print_quoat(str, &i, pipefd) > 0)
				continue ;
		if (str[i] == '$' && str[i + 1])
		{
			if (ft_strcmp(str + i, "$?") == 0)
				ft_putnbr_fd(shell->ecode, pipefd);
			else
			{
				tmp = ft_getenv(str + i + 1, shell);
				if (tmp)
					ft_putstr_fd(tmp, pipefd);
			}
			break ;
		}
		else
			write(pipefd, &str[i], 1);
	}
}

int	check_first_options(char *str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (ft_putstr_fd(str, 1), 1);
		i++;
	}
	return (0);
}

void	echo(char **options, t_shell *shell)
{
	int	i;
	int	no_line;

	shell->ecode = 0;
	if (!options[1])
	{
		write(1, "\n", 1);
		return ;
	}
	i = 1;
	no_line = ft_strncmp(options[1], "-n", 2);
	if (!no_line)
	{
		no_line = check_first_options(options[1]);
		i++;
	}
	while (options[i])
	{
		check_env(options[i], 1, shell);
		i++;
		if (options[i])
			write(1, " ", 1);
	}
	if (no_line)
		write(1, "\n", 1);
}
