/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:29 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/22 11:19:10 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define METACHARACTERS " |&;()<>\t\n"

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
	WRITE_FD,
	BOTH_FDS
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
}	t_redir_type;

typedef enum e_token_type
{
	WORD,
	TILDE_EXPANSION,
	REDIRECTION,
	PIPE,
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

typedef struct s_command
{
	t_list	*tokens;
	t_list	*redirs;
	int		builtin;
}	t_command;

typedef struct s_line
{
	t_list	*cmds;
	int		*fds;
	int		*pids;
	int		nbcommands;
	int		stdinbak;
	int		stdoutbak;
}	t_line;

typedef struct s_data
{
	t_list	*env;
	t_line	*line; // Why static
	int		errcode; // use for $?
}	t_data;

/* core */

int				minishell(t_data *core);
t_var			*get_env(t_data *core, char *key);
t_var			*split_var(char *var_brut);
t_list			*set_env(char **envp);
char			**get_env_array(t_data *core);

/* lexer */

t_list			*lexer(void);
uint8_t			is_identifier(const char *value);
uint8_t			is_flag(const char *value);
uint8_t			is_word_token(const char *value);
char			*handle_odd_quotes(char quote, uint16_t total_quotes, char *str);
int32_t			get_end_quote_idx(const char *str, int32_t i);
int				get_size_metachar(const char *user_input, uint32_t i);
int32_t			get_str_size(const char *user_input, int32_t i);
char			*remove_quotes(char *str, t_token_type type);

/* parser */
void		parser(t_data *core);
t_redir		*initialize_redir(t_token *token);
t_command	*initialize_cmd(void);
t_token		*initialize_identifier(void);
t_line		*initialize_line(void);
t_command	*command(t_list *token_list, t_token **look_ahead);
void		get_next_token(t_list *token_list, t_token **look_ahead);
void		execute_expansions(t_data *core);
char		*find_var(t_list *env, char *key, int errcode);
char		*expand_var_concat(t_list *env, char *value, int errcode);

/* exec */

int				executor(t_data *core); //TODO
int				redirect_input(t_list *redirs, t_fds fds, int *stdinbak, int iscommand);
int				isbuiltin(char *cmdpath); //TODO
char			*get_cmdpath(t_data *core, char *cmd, t_var *envpaths); //TODO
int				hasinput(t_list *redirs);
int				hasoutput(t_list *redirs);
int				set_fds(t_fds *fds, t_data *core, int cmd_nb);
int				close_fds(t_data *core, t_pipe_fds fds);

int				exec_builtin(t_data *core, char *cmdpath, char **args);


/* builtins */

int				ft_pwd(t_data *core);
int				ft_echo(char **args);
int				ft_cd(t_data *core, char **args); //TODO senderror
int				ft_env(t_data *core);
int				ft_export(t_data *core, char **args);
int				export_single(t_data *core, char *arg); // does it go here?
int				ft_unset(t_data *core, char **args);
int				unset_single(t_data *core, char *key); // does it go here?
int				ft_exit(t_data *core, char **args); //TODO senderror

/* utils */

void			free_struct(t_data *core);
void			free_line(t_line *line);
void			free_cmd(void *cont);
void			free_var(void *cont);
void			free_token(void *cont);

int				tmp_parser(t_data *core, char **cmds);

/* errors */
int send_error(char *err_msg, char *detail_msg, int exit_status);

/* printers */

void	print_var_env(void *cont);
void	print_var_exp(void *cont);
void	print_str(void *cont);
void	print_command(void *cont);
void	print_tokens(void *cont);
void	hola(char *str);
void	print_execve(char *cmdpath, char **args, char **envp);

#endif
