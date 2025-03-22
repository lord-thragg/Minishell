/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:26:43 by luluzuri          #+#    #+#             */
/*   Updated: 2025/03/22 18:08:59 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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

/* COLOR */
# define RED "\033[0;31m"
# define WHITE "\x1B[37m"
# define BLACK "\033[0;30m"
# define GREEN "\033[0;32m"
# define MAGENTA "\033[0;35m"
# define CYAN "\033[0;36m"
# define RESET "\033[0m"

/* COMMAND TYPES */
# define CMD 1
# define ARG 2
# define PIPE 3
# define FILE 4
# define REDIN 5
# define REDOUT 6
# define APPEND 7
# define HEREDOC 8
//# define SPACE		10

/* MSG ERROR */
# define ER_MALLOC "Error: malloc allocation failed.\n"
# define ER_SHELL "Error: shell allocation failed.\n"
# define ER_PARSING "Error: Wrong syntax.\n"

/* CODE ERROR */
# define EXT_MALLOC 1
# define EXT_SHELL 2
# define EXT_PARSING 3
# define EXT_COMMAND_NOT_FOUND 127

/* GNL */
# define BUFFER_SIZE 10

extern pid_t		g_sigpid;

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
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}					t_token;

typedef struct s_shell
{
	char			**env;
	t_token			*token;
	t_cmd			*cmd;
	int				ecode;
	int				last_pid;
	int				initin;
	int				initout;
}					t_shell;

/* MAIN */
int					minishell(char **env);

/* PARSING */
int					parsing(t_shell *shell, char *input);
void				add_cmd(t_cmd **head, t_cmd *ncmd);
int					ctoken(t_token *tok);
t_token				*tokenize(char **str);
t_cmd				*token_to_command(t_token *token);
t_token				*determine_type(t_cmd **head, t_cmd **cmd, t_token *token);
char				**ft_splitspace(char const *s);
char				*ft_strndup(const char *s, size_t n);

/* FREE */
void				free_all(t_shell *shell, char *emsg, int ecode);
void				fsplit(char **split, size_t j);
t_token				*free_token(t_token *head);
t_cmd				*free_cmd(t_cmd *head);
void				free_tab(char **str);
char				**ft_freetab(char **tab);

/* SIGNALS */
void				signal_handler(int signum);
void				set_sigact(void);
void				signal_child(void);

/* BULTIN */
void				echo(char **options, t_shell *shell);
void				ft_env(t_shell *shell);
void				export(t_shell *shell);
int					cd(t_shell *shell, char *path);
void				ft_unset(t_shell *shell, char *env_var);
int					ft_pwd(t_shell *shell);
void				ft_exit(t_shell *shell);
void				handle_single_quotes(char **options, int *i,
						t_shell *shell);
void				check_env(char *str, int pipefd, t_shell *shell, int i);
/* ENV	*/
char				*ft_getenv(char *env_variable, t_shell *shell);
int					ft_getenv_pos(char *env_variable, t_shell *shell);

/*UTILS*/
char				**append_str(char **tab, char *str);

/* EXECUTION */
void				simple_execution(t_cmd *cmd, t_shell *shell, int pipin,
						int pipout);
void				execute_cmd(t_shell *shell);
int					manage_infile(char **files, t_cmd *cmd);
int					manage_outfile(char **files, int append);
char				*find_path(char *program, t_shell *shell);
int					execute_bultins(char *str, t_shell *shell);
int					check_is_relative_path(char *program);
void				choose_infile_order(t_shell *shell);

/* HEREDOCS */
void				do_all_heredocs(char **heredocs);

/* GNL */
char				*get_next_line(int fd);

#endif