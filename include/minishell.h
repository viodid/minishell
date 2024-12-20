/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:29 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/11/28 19:48:23 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef HOSTNAME
#  define HOSTNAME		"host"
# endif

# define METACHARACTERS " |<>\t\n"

# define GRN_BOLD		"\001\033[1;32m\002"
# define BLU_BOLD		"\001\033[1;34m\002"
# define RES			"\001\033[0m\002"

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

/*================================== ENUMS ===================================*/

typedef enum e_pipe_fds
{
	READ_FD,
	WRITE_FD
}	t_pipe_fds;

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

typedef enum s_mode
{
	INTER,
	NONIN
}	t_shell_mode;

/*================================= STRUCTS ==================================*/

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
}	t_redir;

/**
 * A single command, it contains:
 * - `tokens`: linked list, contains `t_token` structures
 * - `redirs`: linked list, contains `t_redir` structures
 */
typedef struct s_command
{
	t_list	*tokens;
	t_list	*redirs;
	t_fds	fds;
}	t_command;

/**
 * A line of commands, contains:
 * - `cmds`: linked list, contains `t_command` structures
 * - `fds`: 2D array of integers, contains pipe file descriptors
 * - `pids`: array of integers, contains process IDs
 * - `nbcommands`: integer, contains the number of commands
 */
typedef struct s_line
{
	t_list	*cmds;
	int		**fds;
	int		*pids;
	int		nbcommands;
	int		haschild;
}	t_line;

/**
 * Minishell's core, contains:
 * - `env`: linked list, contains environment variables
 * - `line`: structure, contains a line of commands
 * - `errcode`: integer, stores error codes
 * - `sv_stdin`: integer, saves the standard input fd
 * - `sv_stdout`: integer, saves the standard output fd
 */
typedef struct s_data
{
	t_list	*env;
	t_line	*line;
	int		errcode;
	int		sv_stdin;
	int		sv_stdout;
}	t_data;

/*=================================== core ===================================*/

int			minishell(t_data *core);
t_var		*get_env(t_data *core, char *key);
t_var		*split_var(char *var_brut);
char		**get_env_array(t_list *env);
int			init_core(t_data *core, char **argv, char **envp);

/*================================= signals ==================================*/

void		signal_handler(t_shell_mode mode);

/*================================== lexer ===================================*/

t_list		*lexer(t_data *core);
char		*get_prompt(t_list *env);
void		insert_token(char *value, t_list **token_list, int parse_quotes);
uint8_t		is_word_token(const char *value);
int32_t		get_next_quote_idx(const char *str, int32_t i);
int			get_size_metachar(const char *user_input, uint32_t i);
int32_t		get_str_size(const char *user_input, int32_t i);
char		*remove_quotes(char *str);

/*================================== parser ==================================*/

void		parser(t_data *core);
t_redir		*initialize_redir(t_token *token);
t_command	*initialize_cmd(void);
t_token		*initialize_token(void);
t_line		*initialize_line(void);
t_command	*command(t_list *token_list, t_token **look_ahead);
void		get_next_token(t_list *token_list, t_token **look_ahead);
t_list		*execute_expansions(t_list *token_list, const t_list *env, int err);
char		*find_var(const t_list *env, char *key, int errcode);
char		*expand_var_concat(const t_list *env,
				const char *value, int errcode);

/*=================================== exec ===================================*/

int			executor(t_data *core);
int			get_redirs(t_command *command, t_fds *fds);
int			get_infiles(t_list *redirs, t_fds *fds, int iscommand);
int			get_outfiles(t_list *redirs, t_fds *fds);
int			isbuiltin(char *cmdpath);
char		*get_cmdpath(char *cmd, t_var *envpaths);
char		**get_arg_array(t_command *command);
int			hasinput(t_list *redirs);
int			hasoutput(t_list *redirs);
int			set_fds(t_fds *fds, t_data *core, int cmd_nb);
int			close_fds(t_fds *fds);
int			reset_stdfds(t_data *core);
int			save_stdfds(t_data *core);
int			init_pipes(t_data *core);
int			do_heredocs(t_data *core);
int			do_fileredir(t_command *command, t_fds fds);
int			exec_builtin(t_data *core, char *cmdpath, char **args);
int			do_piperedir(t_data *core, int cmd_nb);
int			close_parent_pipes(t_data *core, int cmd_nb);

/*================================= builtins =================================*/

int			ft_pwd(t_data *core);
int			ft_echo(char **args);
int			ft_cd(t_data *core, char **args);
int			ft_env(t_data *core);
int			ft_export(t_data *core, char **args);
int			export_single(t_data *core, char *arg);
int			ft_unset(t_data *core, char **args);
int			ft_exit(t_data *core, char **args, int ischild);

/*================================== utils ===================================*/

void		free_struct(t_data *core);
void		free_line(t_line *line);
void		free_cmd(void *cont);
void		free_var(void *cont);
void		free_token(void *cont);

/*================================== errors ==================================*/

int			send_error(char *err_msg, char *detail_msg, int exit_status);

/*================================= printers =================================*/

void		print_var_env(void *cont);
void		print_var_exp(void *cont);

// void		print_command(void *cont);
// void		print_redirs(void *cont);
// void		print_tokens(void *cont);
// void		print_execve(char *cmdpath, char **args, char **envp);
// void		print_fds(t_fds fds);

#endif
