/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:26:43 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/30 17:30:33 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# include "libft.h"
# include "minishell_str.h"

/* COLOR */
# define RED "\033[0;31m"
# define WHITE "\x1B[37m"
# define BLACK "\033[0;30m"
# define GREEN "\033[0;32m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

/* PARSING */
# define BSIZE 4096

/* COMMAND TYPES */
# define CMD 1
# define ARG 2
# define PIPE 3
# define FILE 4
# define REDIN 5
# define REDOUT 6
# define APPEND 7
# define HEREDOC 8

/* MSG ERROR */
# define ER_MALLOC		"Error: malloc allocation failed.\n"
# define ER_BUFF		"Error: buffer overflow handled.\n"
# define ER_SHELL		"Error: shell allocation failed.\n"
# define ER_PARSING		"Error: Wrong syntax.\n"

/* CODE ERROR */
# define OK 0
# define KO 1
# define EXT_SHELL 2
# define EXT_PARSING 3
# define EXT_COMMAND_NOT_FOUND 127

/* GNL */
# define BUFFER_SIZE 10

/* PARSING */
void	ft_lstclear_cust(t_list **lst, void (*del)(void *));
int		parsing(t_shell *shell, t_list *token, char *input);
int		tokenize(t_list **token, char *input);
void	print_t(t_list *token);
void	free_all(void);

#endif