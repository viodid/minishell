/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:12:21 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/08 19:08:51 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(void *cont)
{
	t_token	*token;

	token = (t_token *)cont;
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	free(cont);
}

void	free_redir(void *cont)
{
	t_redir	*redir;

	redir = (t_redir *)cont;
	if (redir->file)
	{
		free(redir->file);
		redir->file = NULL;
	}
	free(redir);
}

void	free_cmd(void *cont)
{
	t_command	*command;

	command = (t_command *)cont;
	if (command->redirs)
		ft_lstclear(&command->redirs, free_redir);
	if (command->tokens)
		ft_lstclear(&command->tokens, free_token);
}

void	free_var(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	free(var->key);
	free(var->value);
}

void	free_struct(t_data *core)
{
	ft_lstclear(&core->env, free_var);
	ft_lstclear(&core->line->cmds, &free_cmd);
}
