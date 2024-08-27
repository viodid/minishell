/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:29 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/28 00:24:30 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# define TRUE 1
# define FALSE 0
# define NULL ((void *)0)

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <errno.h>

# define HDOC_TMP	"_tmphdoc"

/* ENUMS */
typedef enum e_tmp_pos
{
	NBTOK,
	ICMD,
	IOUTREDIR,
}	t_tmp_pos;

typedef enum e_token_type
{
	COMMAND,
	ARGUMENT,
}	t_token_type;

typedef enum e_redir_type
{
	HEREDOC,
	INPUT,
	OUTPUT,
	APPEND,
}	t_redir_type;

/* STRUCTS */
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
	int		stdinbak;
}	t_line;

typedef struct s_data
{
	t_list	*env;
	t_line	line;
}	t_data;

/* core */

int		minishell(t_data *core);
t_var	*get_env(t_data *core, char *key);
t_var	*split_var(char *var_brut);
t_list	*set_env(char **envp);
char	**get_env_array(t_data *core);

/* exec */

int		executor(t_data *core);
int		redirect_input(t_list *redirs, int *stdinbak);
int		isbuiltin(t_command *cmd);
int		exec_builtin(t_data *core, char *path, char **args, char **envp);


/* builtins */

int		ft_pwd(t_data *core);
int		ft_echo(int option, char **args);
int		ft_cd(t_data *core, char *dest);
int		ft_env(t_data *core);
int		ft_export(t_data *core, char *var);
int		ft_unset(t_data *core, char *key);
int		ft_exit(t_data *core);

/* utils */

void	free_struct(t_data *core);
void	free_var(void *cont);
void	free_cmd(void *cont);

int		temp_parser(t_data *core, char **cmds);

/* printers */

void	print_var(void *cont);
void	print_str(void *cont);
void	print_command(void *cont);
void	hola(char *str);

#endif
