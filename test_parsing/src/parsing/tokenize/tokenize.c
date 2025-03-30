/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 14:04:36 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/30 14:48:31 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	hoverflow(t_list **token)
{
	ft_putchar_fd("Error: buffer overflow handled.\n", 2);
	ft_lstclear_cust(token, free);
	return (2);
}

static int	handle_quotes(char **loop, t_list **token, char *buffer)
{
	
}

static int	process(char **loop, t_list **token, char *buffer, int *i)
{
	if (*i == BSIZE)
	{
		if (hoverflow(token) != OK)
			return (KO);
		*i = 0;
	}
	else if (**loop == 34 || **loop == 39)
	{
		if (handle_quotes(loop, token, buffer) == KO)
			return (KO);
		*i = 0;
	}
}

int	tokenize(t_list **token, char *input)
{
	int		i;
	char	*loop;
	char	buffer[BSIZE];

	i = 0;
	ft_bzero(buffer, BSIZE);
	loop = input;
	while (*loop)
	{
		if (process(&loop, token, buffer, &i) == KO)
			return (KO);
	}
	if (ft_strlen(buffer) > 0)
		add_token();
	return (OK);
}
