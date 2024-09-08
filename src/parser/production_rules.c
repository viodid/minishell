/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:33:21 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/08 00:23:51 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_word(t_token *look_ahead)
{
	t_token_type	type;

	type = look_ahead->type;
	if (type == IDENTIFIER || type == VARIABLE || type == TILDE_EXPANSION
		|| type == SINGLE_QUOTE_STRING || type == DOUBLE_QUOTE_STRING)
		return (TRUE);
	return (FALSE);
}

static void	options(t_list *token_list, t_token **look_ahead, t_command *cmd)
{
	t_token	*id;

	while (*look_ahead && (is_word(*look_ahead) || (*look_ahead)->type == FLAG))
	{
		id = initialize_identifier();
		id->type = (*look_ahead)->type;
		id->value = ft_strdup((*look_ahead)->value);
		get_next_token(token_list, look_ahead);
		ft_lstadd_back(&cmd->tokens, ft_lstnew(id));
	}
}

static void	command_name(t_list *token_list, t_token **look_ahead, t_command *cmd)
{
	t_token	*id;
	t_list	*id_list;

	id_list = NULL;
	if (*look_ahead == NULL || !is_word(*look_ahead))
	{
		if (!errno)
			send_error("syntax error near unexpected token: ", (*look_ahead)->value, 1);
		errno = 42;
		return ;
	}
	id = initialize_identifier();
	id->type = (*look_ahead)->type;
	id->value = ft_strdup((*look_ahead)->value);
	get_next_token(token_list, look_ahead);
	ft_lstadd_back(&id_list, ft_lstnew(id));
	cmd->tokens = id_list;
}

static void	redirection(t_list *token_list, t_token **look_ahead, t_command *cmd)
{
	t_redir		*redir;
	t_list		*redir_list;

	while (*look_ahead && (*look_ahead)->type == REDIRECTION)
	{
		redir = initialize_redir(*look_ahead);
		get_next_token(token_list, look_ahead);
		if (*look_ahead == NULL || !is_word(*look_ahead))
		{
			if (!errno)
				send_error("syntax error near unexpected token: ", (*look_ahead)->value, 1);
			errno = 42;
			return ;
		}
		redir->file = ft_strdup((*look_ahead)->value);
		ft_lstadd_back(&cmd->redirs, ft_lstnew(redir));
		get_next_token(token_list, look_ahead);
	}
}

static t_command	*command(t_list *token_list, t_token **look_ahead)
{
	t_command	*cmd;

	cmd = initialize_cmd();
	redirection(token_list, look_ahead, cmd);
	command_name(token_list, look_ahead, cmd);
	redirection(token_list, look_ahead, cmd);
	options(token_list, look_ahead, cmd);
	redirection(token_list, look_ahead, cmd);
	if (errno)
	{
		free_cmd(cmd);
		return (NULL);
	}
	return (cmd);
}

static t_list	*full_command(t_list *token_list, t_token	**look_ahead)
{
	t_list		*cmd_list;
	t_command	*cmd;

	cmd_list = NULL;
	cmd = command(token_list, look_ahead);
	while (cmd)
	{
		ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
		if (*look_ahead && (*look_ahead)->type == PIPE)
		{
			get_next_token(token_list, look_ahead);
			cmd = command(token_list, look_ahead);
		}
		else
			cmd = NULL;
	}
	return (cmd_list);
}

t_list	*descent_parser(t_list *token_list)
{
	t_list	*cmds;
	t_token	*look_ahead;

	look_ahead = (t_token *)token_list->content;
	cmds = full_command(token_list, &look_ahead);
	return (cmds);
}
