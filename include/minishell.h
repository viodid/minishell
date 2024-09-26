/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:29 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/26 21:54:53 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define METACHARACTERS " |<>\t\n"

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

# define HDOC_TMP	"_tmphdoc"

/* ENUMS */
typedef enum e_pipe_fds
{
	READ_FD,
	WRITE_FD
}	t_pipe_fds;

typedef enum e_tmp_pos
{
	NBTOK,
	ICMD,
	IOUTREDIR,
}	t_tmp_pos;

typedef enum e_redir_type
{
	HEREDOC,
	INPUT,
	OUTPUT,
	APPEND,
	H_INPUT,
}	t_redir_type;

typedef enum e_token_type
{
	WORD,
	REDIRECTION,
	PIPE,
	SINGLE_QUOTES,
	DOUBLE_QUOTES
}	t_token_type;

/* STRUCTS */


typedef struct s_fds
{
	int	stdfdin;
	int	fdin;
	int	stdfdout;
	int	fdout;
}	t_fds;

typedef struct s_var
{
	char	*key;
	char	*value;
}	t_var;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
}	t_token;

typedef struct s_redir
{
	char			*file;
	t_redir_type	type;
	t_token_type	token_type;
}	t_redir;

/**
 * A single command, it contains:
 * - `tokens`: a linked list of tokens, contains `t_token` structures
 * - `redirs`: a linked list of redirections, contains `t_redir` structures
 */
typedef struct s_command
{
	t_list	*tokens;
	t_list	*redirs;
	t_fds	fds;
	int		builtin;
}	t_command;

/**
 * A line of commands, it contains:
 * - `cmds`: a linked list of commands, contains `t_command` structures
 * - `fds`: a 2D array of ints representing file descriptors
 * - `pids`: an array of ints representing process IDs
 * - `nbcommands`: an int representing the number of commands
 */
typedef struct s_line
{
	t_list	*cmds;
	int		**fds;
	int		*pids;
	int		nbcommands;
}	t_line;

/**
 * Minishell's core, it cotains:
 * - `env`: a linked list of environment variables
 * - `line`: a structure containing a line of commands
 * - `errcode`: an int to store error codes
 * - `sv_stdin`: an int to save the standard input fd
 * - `sv_stdout`: an int to save the standard output fd
 */
typedef struct s_data
{
	t_list	*env;
	t_line	*line;
	int		errcode;
	int		sv_stdin;
	int		sv_stdout;
}	t_data;

/* core */

int				minishell(t_data *core);
t_var			*get_env(t_data *core, char *key);
t_var			*split_var(char *var_brut);
char			**get_env_array(t_data *core);
int				init_core(t_data *core, char **argv, char **envp);

/* lexer */

t_list		*lexer(void);
void		insert_token(char *value, t_list **token_list, int parse_quotes);
uint8_t		is_identifier(const char *value);
uint8_t		is_flag(const char *value);
uint8_t		is_word_token(const char *value);
char		*handle_odd_quotes(char quote, uint16_t total_quotes, char *str);
int32_t		get_next_quote_idx(const char *str, int32_t i);
int			get_size_metachar(const char *user_input, uint32_t i);
int32_t		get_str_size(const char *user_input, int32_t i);
char		*remove_quotes(char *str);

/* parser */
void		parser(t_data *core);
t_redir		*initialize_redir(t_token *token);
t_command	*initialize_cmd(void);
t_token		*initialize_identifier(void);
t_line		*initialize_line(void);
t_command	*command(t_list *token_list, t_token **look_ahead);
void		get_next_token(t_list *token_list, t_token **look_ahead);
t_list		*execute_expansions(t_list *token_list, const t_list *env, int errcode);
char		*find_var(const t_list *env, char *key, int errcode);
char		*expand_var_concat(const t_list *env, char *value, int errcode);

int			tmp_parser(t_data *core, char **cmds);

/* exec */

int				executor(t_data *core); //TODO //TODO
int				get_redirs(t_command *command, t_fds *fds);
int				get_infiles(t_list *redirs, t_fds *fds, int iscommand);
int				get_outfiles(t_list *redirs, t_fds *fds);
int				isbuiltin(char *cmdpath);
char			*get_cmdpath(t_data *core, char *cmd, t_var *envpaths);
char			**get_arg_array(t_command *command);
int				hasinput(t_list *redirs);
int				hasoutput(t_list *redirs);
int				set_fds(t_fds *fds, t_data *core, int cmd_nb);
int				reset_stdfds(t_data *core);
int				save_stdfds(t_data *core);
int				init_pipes(t_data *core);
int				do_heredocs(t_list *commands);
int				do_fileredir(t_command *command, t_fds fds);
int				exec_builtin(t_data *core, char *cmdpath, char **args, int is_exit);
int				do_piperedir(t_data *core, t_command *command, t_fds fds, int cmd_nb);
int				close_parent_pipes(t_data *core, int cmd_nb);

/* builtins */

int				ft_pwd(t_data *core);
int				ft_echo(char **args);
int				ft_cd(t_data *core, char **args); //TODO senderror
int				ft_env(t_data *core);
int				ft_export(t_data *core, char **args); //TODO
int				export_single(t_data *core, char *arg);
int				ft_unset(t_data *core, char **args);
int				unset_single(t_data *core, char *key);
int				ft_exit(t_data *core, char **args, int cmd_nb); //TODO senderror

/* utils */

void			free_struct(t_data *core);
void			free_line(t_line *line);
void			free_cmd(void *cont);
void			free_var(void *cont);
void			free_token(void *cont);
void			free_line(t_line *line);

int				tmp_parser(t_data *core, char **cmds);

/* errors */
int send_error(char *err_msg, char *detail_msg, int exit_status);

/* printers */

void	print_var_env(void *cont);
void	print_var_exp(void *cont);
void	print_str(void *cont);
void	print_command(void *cont);
void	print_tokens(void *cont);
int		hola(char *str);
void	print_execve(char *cmdpath, char **args, char **envp);
void	print_fds(t_fds fds);

#endif
