/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:58:20 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/29 20:17:14 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_var(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	printf("%s=%s\n", var->key, var->value);
}

void	print_str(void *cont)
{
	printf("%s\n", (char *)cont);
}

void	print_redirs(void *cont)
{
	t_redir	*redir;

	redir = (t_redir *)cont;
	printf(" redir %i to %s\n", redir->type, redir->file);
}

void	print_tokens(void *cont)
{
	t_token	*token;

	token = (t_token *)cont;
	printf(" token %s\n type %i\n", token->value, token->type);
}

void	print_command(void *cont)
{
	t_command	*command;

	command = (t_command *)cont;
	printf("printing command:\n");
	ft_lstiter(command->redirs, print_redirs);
	ft_lstiter(command->tokens, print_tokens);
	printf("\n");
}

void	print_execve(char *path, char **args, char **envp)
{
	int	i;
	(void)envp;

	i = 0;
	printf("command :%s\n", path);
	printf("args :\n");
	while (printf("->%i\n", i) && args[i])
		printf("%s\n", args[i++]);
	// i = -1;
	// while (envp[++i])
	// 	hola(envp[i]);
}

void	hola(char *str)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
}
