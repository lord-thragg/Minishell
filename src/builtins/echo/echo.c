/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:08:34 by lle-duc           #+#    #+#             */
/*   Updated: 2025/04/19 11:33:23 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_quoat(char *str, int *i, int pipefd)
{
	int		j;
	char	quote;

	quote = str[*i];
	j = *i + 1;
	write(pipefd, &quote, 1);
	while (str[j])
	{
		if (str[j] == quote)
		{
			*i = *i + 1;
			while (*i < j)
			{
				write(pipefd, &str[*i], 1);
				(*i)++;
			}
			write(pipefd, &quote, 1);
			return (j);
		}
		j++;
	}
	return (0);
}

void	expand_env_var(char *str, int *i, int pipefd, t_shell *shell)
{
	int		j;
	char	*tmp;
	char	*value;

	j = *i + 1;
	while (str[j] && (ft_isalnum(str[j]) || str[j] == '_'))
		j++;
	if (str[*i + 1] == '?')
	{
		ft_putnbr_fd(shell->ecode, pipefd);
		*i += 2;
	}
	else
	{
		tmp = ft_substr(str, *i + 1, j - (*i + 1));
		if (tmp)
		{
			value = ft_getenv(tmp, shell);
			if (value)
				ft_putstr_fd(value, pipefd);
			free(tmp);
		}
		*i = j;
	}
}

void	check_env(char *str, int pipefd, t_shell *shell, int i)
{
	int	in_single_quote;
	int	in_double_quote;

	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			i++;
			continue ;
		}
		if (str[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			i++;
			continue ;
		}
		if (str[i] == '$' && str[i + 1] && !in_single_quote)
			expand_env_var(str, &i, pipefd, shell);
		else
			write(pipefd, &str[i++], 1);
	}
}

static int	check_first_options(char **options)
{
	int	i;
	int	j;
	int	count;

	count = 1;
	i = 1;
	while (options[i])
	{
		j = 1;
		if (options[i][0] == '-')
		{
			while (options[i][j])
			{
				if (options[i][j] && options[i][j] != 'n')
					return (count);
				j++;
			}
			count++;
		}
		else
			return (count);
		i++;
	}
	return (count);
}

void	echo(char **options)
{
	int	i;
	int	count;

	if (!options[1])
	{
		write(1, "\n", 1);
		return ;
	}
	count = check_first_options(options);
	i = count;
	while (options[i])
	{
		ft_putstr_fd(options[i], 1);
		if (options[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (count == 1)
		write (1, "\n", 1);
}
