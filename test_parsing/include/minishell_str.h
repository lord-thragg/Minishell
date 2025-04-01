/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_str.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/30 13:20:25 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/01 09:18:23 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STR_H
# define MINISHELL_STR_H

# include "minishell.h"

typedef struct s_cmd
{
	int				last;
	bool			append;
	char			**infile;
	char			**outfile;
	char			**cmd_list;
	char			**limiters;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_token
{
	char	*str;
	int		type;
	int		quote;
}					t_token;

typedef struct s_shell
{
	char			**env;
	t_list			*token;
	t_cmd			*cmd;
	int				ecode;
	int				last_pid;
	int				initin;
	int				initout;
}					t_shell;

#endif