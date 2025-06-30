/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luluzuri <luluzuri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 19:26:43 by luluzuri          #+#    #+#             */
/*   Updated: 2025/04/20 12:34:58 by luluzuri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
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
# define OK 0
# define KO 1
# define SQUOTE 4
# define DQUOTE 5
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
# define ER_BUFF "Error: buffer overflow handled.\n"
# define ER_MALLOC "Error: malloc allocation failed.\n"
# define ER_SHELL "Error: shell allocation failed.\n"
# define ER_PARSING "Error: Wrong syntax.\n"
# define ER_HEREDOC "here-document at line 3 delimited by end-of-file wanted ('"

/* CODE ERROR */
# define EXT_MALLOC 1
# define EXT_SHELL 2
# define EXT_PARSING 3
# define EXT_COMMAND_NOT_FOUND 127

/* GNL */
# define BUFFER_SIZE 10
# define BSIZE 4096

/* DEBUG */
# define DEBUG 0

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
	int				quote;
	int				sindex;
	int				eindex;
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

typedef struct s_sigmsg
{
	int				sig;
	char			*msg;
}					t_sigmsg;

/* TEST */

/* DEBUG */
void				*singleton_input(void *data);
void				*singleton_fd(void *data);
t_shell				*singleton_shell(t_shell *shell);
int					debug(int *debug_fd, char *str, int debug);

/* MAIN */
int					minishell(char **env);
char				**copy_double_tab(char **env);
int					singleton(int target);

/* PARSING */
int					parser_set(t_shell *shell, t_list *token, char *input);
void				ft_lstclear_cust(t_list **lst, void (*del)(void *));
int					parsing(t_shell *shell, t_list *token, char *input);
int					tokenize(t_list **token, char *input);
t_list				*ft_lstnew_custom(char buffer[BSIZE]);
void				printt(t_list *token);
char				**ft_splitspaces(const char *s);
char				**ft_freetab(char **tab);
int					is_space(char c);
int					count_tokens(const char *s);
char				*alloc_token(const char *start, int len);
char				**free_tokens(char **result, int i);
char				*get_next_token(const char **s, int *len);
char				**fill_tokens(const char *s, char **result,
						int tokens_count);
void				expand_pid(char **str);
int					get_pid_from_proc(void);

/* PARSING COMMANDS */
void				printc(t_cmd *cmd);
t_cmd				*token_to_command(t_list *token);
t_list				*determine_type(t_cmd **head, t_cmd **cmd, t_list *token);
t_cmd				*create_cmd(t_cmd *ncmd, t_list *token);
int					ctoken(t_list *tok);
char				**initiate_file(t_list *token, int flag);
void				put_null(char **tab, int len);
int					ctype(t_list *token, int flag);
t_list				*arg_type(t_cmd **cmd, t_list *token);
t_list				*file_type(t_cmd *cmd, t_list *token);
t_list				*infile_outfile(t_cmd *cmd, t_list *token);
void				add_cmd(t_cmd **head, t_cmd *ncmd);
char				**append_str(char **tab, char *str);
char				*rebuild_str(char **tab);

/* PARSING TOKENIZE */
t_list				*outfile(t_cmd *cmd, t_list *token);
int					hoverflow(t_list **token);
int					twin_quote(char *str);
char				*copy_to_twin(char **loop, char buffer[BSIZE]);
void				add_token(t_list **token, char buffer[BSIZE], char *brut);
int					handle_quotes(char **loop, t_list **token,
						char buffer[BSIZE]);
void				increments(char **prompt_loop, char *buffer, int *i);
int					check_operator(char *loop);
int					check_quote_type(char **loop);
void				set_optype(t_token *token);
void				handle_operator(char **loop, t_list **token,
						char buffer[BSIZE]);
int					process(char **loop, t_list **token, char *buffer, int *i);
void				handle_space(char **prompt_loop, t_list **token,
						char buffer[BSIZE]);
void				merge_joined_tokens(t_list **token_list);
void				*singleton_input(void *data);

/* PARSING EXPAND */
char				*the_join(char *str, char *backup, char *buffer);
char				*strjoin_free(char *backup, char *buffer);
int					condition_for_expand(t_list *token, char *str);
int					has_dollars(char *str);
int					has_multdollars(char *str);
char				*keep_next_str(char **str);
char				*no_surround(char *str, t_shell *shell);
char				*create_expand_dollar(t_shell *shell, char *str,
						char *expanded, int qtype);
char				*dollar_expension(char *str, int qtype, t_shell *shell);
int					build_single(t_shell *shell, char **dollar,
						char **exported);
int					no_otab(char ***original_tab, char *toadd, char ***newtab);
int					countcopy_otab(char ***original, char ***newtab, int *ntab);
int					add_back_tab(char ***dollar_tab, char *toadd);
int					add_doll_ftab(t_shell *shell, char ***dollar_tab);
int					do_expansion(t_shell *shell, char **dollar_tab);
int					add_doll_tab(t_shell *shell, char ***dollar_tab,
						char *exported);
int					fstep_multdollar(t_shell *shell, char ***dollar_tab,
						char **exported);
int					handle_multdollar(t_shell *shell, char ***dollar_tab,
						char **exported);
int					set_dollarsnexpande(t_shell *shell, char ***dollar_tab,
						char ***exported);
int					build_expandnreplace(char **str_expanded, char ***exported,
						char **str);
int					start_expanding(t_shell *shell, char ***dollar_tab,
						char **str);
int					expand(t_shell *shell, t_list **token);

/* FREE */
void				free_all(t_shell *shell, char *emsg, int ecode);
void				fsplit(char **split, size_t j);
t_cmd				*free_cmd(t_cmd *head);
char				**ft_freetab(char **tab);

/* SIGNALS */
void				signal_handler(int signum);
void				set_sigact(void);
void				signal_child(void);
char				*ft_strsignal(int sig);
void				signal_heredoc(void);

/* BULTIN */
void				echo(char **options);
void				ft_env(t_shell *shell);
void				export(t_shell *shell, int i);
void				export_all_env(char *env, t_shell *shell);
char				**split_first(char *env);
char				*recover_full_env(char *init_env, char *new_env_value);
void				change_env_value(t_shell *shell, char *env,
						char *new_value);
int					cd(t_shell *shell, char *path);
void				ft_unset(t_shell *shell, char *env_var);
int					ft_pwd(t_shell *shell);
int					ft_exit(t_shell *shell);
void				check_env(char *str, int pipefd, t_shell *shell, int i);
void				copy_and_display_sorted_env(char **env);

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
int					choose_infile_order(t_shell *shell, t_cmd *cmd,
						int *pipefd);

/* HEREDOCS */
void				do_all_heredocs(char **heredocs, t_shell *shell,
						int *pipefd);
char				*expand_line(char *line, t_shell *shell);

/* GNL */
char				*get_next_line(int fd);

#endif