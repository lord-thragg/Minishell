/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 15:05:33 by lucius            #+#    #+#             */
/*   Updated: 2024/11/12 13:41:06 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*sub;

	sub = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!sub)
		return (sub);
	ft_strlcpy(sub, s, ft_strlen(s) + 1);
	return (sub);
}
