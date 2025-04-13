/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 12:39:02 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/12 12:39:33 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	count_tokens(const char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (is_space(*s))
		{
			count++;
			s++;
		}
		else
		{
			count++;
			while (*s && !is_space(*s))
				s++;
		}
	}
	return (count);
}
