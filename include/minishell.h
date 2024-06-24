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

typedef struct s_var
{
	char	*key;
	char	*value;
}	t_var;

typedef struct s_data
{
	t_list	*envp;
}	t_data;

int		minishell(t_data *core);

t_var	*get_env(char *key, t_data *core);
t_var	*split_var(char *var_brut);
// char	*get_env(char *key, t_data *core);
t_list	*set_env(char **envp);

int		pwd(t_data *core);
int		echo(int option, char *str);
int		cd(char *dest, t_data *core);
int		env(t_data *core);
int		export(t_data *core, char *var);
int		unset(char *key, t_data *core);

/* utils */
void	print_var(void *cont);
void	free_struct(t_data *core);
void	free_var(void *cont);

#endif
