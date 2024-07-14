/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:12:21 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/06/21 17:12:21 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(void *cont)
{
	t_token	*token;

	token = (t_token *)cont;
	free(token->value);
	free(token);
}

void	free_redir(void *cont)
{
	t_redir	*redir;

	redir = (t_redir *)cont;
	free(redir->file);
	free(redir);
}

void	free_cmd(void *cont)
{
	t_command	*command;

	command = (t_command *)cont;
	ft_lstclear(&command->redirs, free_redir);
	ft_lstclear(&command->tokens, free_token);
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
	ft_lstclear(&core->envp, free_var);
	ft_lstclear(&core->cmds, free_cmd);
}
