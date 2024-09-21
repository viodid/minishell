/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:29 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/11 00:31:27 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define METACHARACTERS " \"\'|&;()<>\t\n"

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/wait.h>

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
}	t_redir_type;

typedef enum e_token_type
{
	IDENTIFIER, // https://en.wikipedia.org/wiki/Identifier_(computer_languages)
	VARIABLE,
	SINGLE_QUOTE_STRING,
	DOUBLE_QUOTE_STRING,
	TILDE_EXPANSION,
	REDIRECTION,
	PIPE,
	FLAG
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
	int		**fds;
	int		*pids;
	int		nbcommands;
}	t_line;

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
t_list			*set_env(char **envp);
char			**get_env_array(t_data *core);

/* lexer */

t_list			*lexer(void);
char			*handle_odd_quotes(char quote, uint16_t total_quotes, char *str);
int32_t			get_end_quote_idx(const char *str, int32_t i);
t_token_type	enum_token_value(const char *value);
int				get_size_metachar(const char *user_input, uint32_t i);
int32_t			get_str_size(const char *user_input, int32_t i);

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
char		*expand_var_quotes(t_list *env, char *value, int errcode);

int			tmp_parser(t_data *core, char **cmds);

/* exec */

int				executor(t_data *core); //TODO //TODO
int				redirect_files(t_command *command, t_fds *fds);
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
int				ft_exit(t_data *core, char **args); //TODO senderror

/* utils */

void			free_struct(t_data *core);
void			free_var(void *cont);
void			free_cmd(void *cont);
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

