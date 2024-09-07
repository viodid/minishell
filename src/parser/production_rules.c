/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:33:21 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/07 18:57:29 by dyunta           ###   ########.fr       */
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

static t_list	*redirection(t_list *token_list, t_token *look_ahead)
{
	t_list	*cmds;
	t_redir	*redir;

	cmds = NULL;
	if (look_ahead->type != REDIRECTION)
		return (NULL);
	redir = create_redir(look_ahead);
	look_ahead = get_next_token(token_list, look_ahead);
	if (!is_word(look_ahead))
		return (NULL);
	redir->file = look_ahead->value;
	ft_lstadd_back(&cmds, ft_lstnew(redir));
	return (cmds);
}

static t_list	*command(t_list *token_list, t_token *look_ahead)
{
	t_list	*cmds;

	cmds = redirection(token_list, look_ahead);
	if (errno)
		return (NULL);
	return (cmds);
}


static t_list	*full_command(t_list *token_list, t_token	*look_ahead)
{
	t_list	*cmds;

	cmds = command(token_list, look_ahead);
	return (cmds);
}

t_list	*RDP(t_list *token_list)
{
	t_list	*cmds;
	t_token	*look_ahead;

	look_ahead = (t_token *)token_list->content;
	cmds = full_command(token_list, look_ahead);
	return (cmds);
}
