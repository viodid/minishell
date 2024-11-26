/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers_debug.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:25:48 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/11/25 16:25:48 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

void	print_fds(t_fds fds)
{
	ft_fdprintf(2, "-----\n");
	ft_fdprintf(2, "%i\n", getpid());
	ft_fdprintf(2, "stdin %i\n", fds.stdfdin);
	ft_fdprintf(2, "fdin %i\n", fds.fdin);
	ft_fdprintf(2, "stdout %i\n", fds.stdfdout);
	ft_fdprintf(2, "fdout %i\n", fds.fdout);
	ft_fdprintf(2, "-----\n");
}

void	print_command(void *cont)
{
	t_command	*command;

	command = (t_command *)cont;
	printf("printing command:\n");
	ft_lstiter(command->redirs, print_redirs);
	ft_lstiter(command->tokens, print_tokens);
	print_fds(command->fds);
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
