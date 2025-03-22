/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 13:51:38 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/22 13:53:33 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_single_quotes(char **options, int *i, t_shell *shell)
{
	int	len;

	if (options[*i + 2] && ft_strcmp(options[*i], "'") == 0
		&& ft_strcmp(options[*i + 2], "'") == 0)
	{
		write(1, "'", 1);
		check_env(options[*i + 1], 1, shell, 0);
		write(1, "'", 1);
		*i += 3;
	}
	else
	{
		len = ft_strlen(options[*i]);
		if (len >= 2 && options[*i][0] == '\'' && options[*i][len - 1] == '\'')
			write(1, options[*i] + 1, len - 2);
		else
			check_env(options[*i], 1, shell, 0);
		(*i)++;
	}
}
