/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:26:43 by luluzuri          #+#    #+#             */
/*   Updated: 2025/02/16 10:15:06 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/* COLOR */
# define RED			"\033[0;31m"
# define WHITE			"\x1B[37m"
# define BLACK          "\033[0;30m"
# define GREEN          "\033[0;32m"
# define MAGENTA        "\033[0;35m"
# define CYAN           "\033[0;36m"
# define RESET          "\033[0m"

/* COMMAND TYPES */
# define CMD		1
# define OPT		2
# define ARG		3
# define PIPE		4
# define FILE		5
# define REDIN		6
# define REDOUT		7
# define APPEND		8
# define HEREDOC	9
//# define SPACE		10

/* MSG ERROR */
# define ER_MALLOC	"malloc error.\n"
# define ER_SHELL	"shell error.\n"
# define ER_PARSING	"parsing error.\n"

/* CODE ERROR */
# define EXT_MALLOC 	1
# define EXT_SHELL 		2
# define EXT_PARSING	3

extern pid_t	g_sigpid;

typedef struct s_cmd
{
	bool			skip_cmd;
	int				infile;
	int				outfile;
	char			**cmd_param;
	struct s_cmd	*prev;
	struct s_cmd	*next;
}				t_cmd;

typedef struct s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef struct s_shell
{
	char	**env;
	t_token	*token;
	t_cmd	*cmd;
	int		ecode;
}	t_shell;

/* MAIN */
int		minishell(char **env);

/* PARSING */
int		parsing(t_shell *shell, char *input);
t_token	*tokenize(char **str);

/* FREE */
void	free_all(t_shell *shell, char *emsg, int ecode);
void	free_token(t_token *head);
void	free_tab(char **str);

/* SIGNALS */
void	signal_handler(int signum);
void	set_sigact(void);

/* PROGRAMS */

#endif