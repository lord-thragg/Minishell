/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 11:08:34 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/22 13:51:58 by lle-duc          ###   ########.fr       */
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
		handle_single_quotes(options, &i, shell);
		if (options[i])
			write(1, " ", 1);
	}
	if (no_line)
		write(1, "\n", 1);
	shell->ecode = 0;
}
