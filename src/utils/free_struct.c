/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:12:21 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/14 13:19:39 by dyunta           ###   ########.fr       */
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

void	free_redir(void *cont)
{
	t_redir	*redir;

	redir = (t_redir *)cont;
	free(redir->file);
	redir->file = NULL;
	free(redir);
}

void	free_cmd(void *cont)
{
	t_command	*command;

	command = (t_command *)cont;
	ft_lstclear(&command->redirs, free_redir);
	ft_lstclear(&command->tokens, free_token);
	free(command);
}

void	free_var(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	free(var->key);
	free(var->value);
	free(var);
}

void	free_struct(t_data *core)
{
	ft_lstclear(&core->env, free_var);
	ft_lstclear(&core->line->cmds, &free_cmd);
}
