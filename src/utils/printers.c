/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:58:20 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/07 19:01:57 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_var_env(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	printf("%s", var->key);
	if (var->value)
		printf("=%s", var->value);
	printf("\n");
}

void	print_var_exp(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	printf("declare -x %s", var->key);
	if (var->value)
		printf("=\"%s\"", var->value);
	printf("\n");
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

void	print_execve(char *cmdpath, char **args, char **envp)
{
	int	i;
	(void)envp;

	i = 0;
	printf("command :%s\n", cmdpath);
	printf("args :\n");
	while (printf("->%i\n", i) && args[i])
		printf("%s\n", args[i++]);
}

int	hola(char *str)
{
	int	ret;

	ret = 0;
	if (str)
		ret = write(2, str, ft_strlen(str));
	ret += write(2, "\n", 1);
	return(ret);
}

void	print_fds(t_fds fds)
{
	dprintf(2, "-----\n");
	dprintf(2, "%i\n", getpid());
	dprintf(2, "stdin %i\n", fds.stdfdin);
	dprintf(2, "fdin %i\n", fds.fdin);
	dprintf(2, "stdout %i\n", fds.stdfdout);
	dprintf(2, "fdout %i\n", fds.fdout);
	dprintf(2, "-----\n");
}
