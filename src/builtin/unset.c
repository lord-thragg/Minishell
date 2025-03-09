/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 08:27:18 by lle-duc           #+#    #+#             */
/*   Updated: 2025/03/09 08:27:43 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char **copy_wanted_parts(int env_pos, t_shell *shell)
{
    char **newtab;
    int i;
    int j;
    
    i = 0;
    while (shell->env[i])
        i++;
    newtab = malloc(sizeof(char *) * i);
    newtab[i - 1] = NULL;
    i = 0;
    j = 0;
    while (shell->env[i])
    {
        if (i != env_pos)
        {
            newtab[j] = ft_strdup(shell->env[i]);
            j++;
        }
        i++;
    }
    ft_freetab(shell->env);
    return (newtab);
}

void    ft_unset(t_shell *shell, char *env_var)
{
    int env_pos;

    if (ft_getenv(env_var, shell) != NULL)
    {
        env_pos = ft_getenv_pos(env_var, shell);
        shell->env = copy_wanted_parts(env_pos, shell);
    	shell->ecode = 0;
    }
	shell->ecode = 1;
}
