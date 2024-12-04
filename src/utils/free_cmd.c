/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 15:53:31 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/11/25 15:53:31 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(void *cont)
{
	t_token	*token;

	token = (t_token *)cont;
	free(token->value);
	token->value = NULL;
	free(cont);
}

static void	free_redir(void *cont)
{
	t_redir	*redir;

	redir = (t_redir *)cont;
	if (redir->file)
	{
		free(redir->file);
		redir->file = NULL;
	}
	free(cont);
}

void	free_cmd(void *cont)
{
	t_command	*command;

	command = (t_command *)cont;
	if (command->redirs)
		ft_lstclear(&command->redirs, free_redir);
	if (command->tokens)
		ft_lstclear(&command->tokens, free_token);
	close_fds(&command->fds);
	free(cont);
}
