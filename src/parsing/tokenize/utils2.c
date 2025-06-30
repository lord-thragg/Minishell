/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:30:57 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/12 12:31:15 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hoverflow(t_list **token)
{
	ft_putstr_fd(ER_BUFF, 2);
	ft_lstclear_cust(token, free);
	return (2);
}

int	twin_quote(char *str)
{
	int		i;
	char	quote;

	i = 1;
	quote = str[0];
	while (str[i])
	{
		if (str[i] == quote)
			return (OK);
		i++;
	}
	return (KO);
}

char	*copy_to_twin(char **loop, char buffer[BSIZE])
{
	int		i;
	char	occ;

	i = 0;
	occ = **loop;
	(*loop)++;
	while (**loop != occ)
	{
		buffer[i] = **loop;
		i++;
		(*loop)++;
	}
	(*loop)++;
	return (buffer);
}
