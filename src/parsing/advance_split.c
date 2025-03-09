/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:32:14 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/08 11:34:39 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	advance_to_next_segment(const char *s, char c, size_t i, int *in_quote)
{
	while (s[i] == c && !(*in_quote))
		i++;
	return (i);
}

size_t	advance_through_segment(const char *s, char c, size_t i, int *in_quote)
{
	while ((s[i] && s[i] != c) || (*in_quote && i < ft_strlen(s)))
	{
		if (s[i] == '"' || s[i] == '\'')
			*in_quote = !(*in_quote);
		i++;
	}
	return (i);
}