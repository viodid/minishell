/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:29 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/03/22 18:27:31 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>

typedef enum e_token_type
{
	COMMAND,
	OPTION,
	ARGUMENT,
	REDIRECTION,
	APPEND,
	INFILE,
	OUTFILE,
}	t_token_type;

typedef struct s_var
{
	char	*key;
	char	*value;
}	t_var;

typedef struct s_token
{
	char	*value;
	int		type;
}	t_token;

typedef struct s_command
{
	t_list	*tokens;
	int		nb_tokens;
	int		i_cmd;
}	t_command;

/* REDIR INF REDIR INF CMD OPT ARG ARG REDIR OUTF REDIR OUTF */

typedef struct s_data
{
	t_list	*envp;
	t_list	*cmds;
}	t_data;

int		minishell(t_data *core);

t_var	*get_env(t_data *core, char *key);
t_var	*split_var(char *var_brut);
t_list	*set_env(char **envp);

int		pwd(t_data *core);
int		echo(int option, char *str);
int		cd(t_data *core, char *dest);
int		env(t_data *core);
int		export(t_data *core, char *var);
int		unset(t_data *core, char *key);
int		builtin_exit(t_data *core);

/* utils */
void	print_var(void *cont);
void	free_struct(t_data *core);
void	free_var(void *cont);

#endif
