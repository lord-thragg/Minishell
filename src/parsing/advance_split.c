/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advance_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 10:32:14 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/22 12:29:35 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* size_t	advance_to_next_segment(const char *s, size_t i, int *in_quote)
{
	while ((s[i] == ' ' || s[i] == '\t') && !(*in_quote))
		i++;
	return (i);
}

size_t	advance_through_segment(const char *s, size_t i, int *in_quote)
{
	if (s[i] == '|' && !(*in_quote))
		return (i + 1);
	while (s[i] && ((s[i] != ' ' && s[i] != '\t' && s[i] != '|')
			|| (*in_quote)))
	{
		if (s[i] == '\'' || s[i] == '"')
			*in_quote = !(*in_quote);
		i++;
	}
	return (i);
} */
