/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lle-duc <lle-duc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:18:18 by lle-duc           #+#    #+#             */
/*   Updated: 2025/02/27 16:44:22 by lle-duc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_no_file_error(char *cmd, char *file, int issue)
{
    if (issue)
    {
        perror(cmd);
        perror(": ");
        perror(file);
        perror("Permission denied");
    }
    else
    {
        perror(cmd);
        perror(": ");
        perror(file);
        perror(": No such file or directory");
    }
}
