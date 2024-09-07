/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:33:21 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/07 20:36:06 by dyunta           ###   ########.fr       */
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
	send_error("syntax error near token: ", look_ahead->value, 1);
	errno = 42;
	return (FALSE);
}

static t_command	*redirection(t_list *token_list, t_token **look_ahead)
{
	t_command	*cmd;
	t_redir		*redir;
	t_list		*redir_list;

	redir_list = NULL;
	if (*look_ahead == NULL || (*look_ahead)->type != REDIRECTION)
		return (NULL);
	redir = initialize_redir(*look_ahead);
	get_next_token(token_list, look_ahead);
	if (*look_ahead == NULL || !is_word(*look_ahead))
		return (NULL);
	redir->file = ft_strdup((*look_ahead)->value);
	cmd = initialize_cmd();
	ft_lstadd_back(&redir_list, ft_lstnew(redir));
	cmd->redirs = redir_list;
	get_next_token(token_list, look_ahead);
	return (cmd);
}

static t_command	*command(t_list *token_list, t_token **look_ahead)
{
	t_command	*cmd;

	cmd = redirection(token_list, look_ahead);
	if (errno)
		return (NULL);
	return (cmd);
}

static t_list	*full_command(t_list *token_list, t_token	**look_ahead)
{
	t_list	*cmd_list;
	t_command	*cmd;

	cmd_list = NULL;
	cmd = command(token_list, look_ahead);
	while (cmd)
	{
		ft_lstadd_back(&cmd_list, ft_lstnew(cmd));
		cmd = command(token_list, look_ahead);
	}
	return (cmd_list);
}

t_list	*RDP(t_list *token_list)
{
	t_list	*cmds;
	t_token	*look_ahead;

	look_ahead = (t_token *)token_list->content;
	cmds = full_command(token_list, &look_ahead);
	return (cmds);
}
