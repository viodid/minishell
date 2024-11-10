/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:33:21 by dyunta            #+#    #+#             */
/*   Updated: 2024/10/23 20:46:03 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static uint8_t	is_identifier(t_token *look_ahead)
{
	uint32_t	i;
	char		*value;

	if (look_ahead == NULL || look_ahead->type != WORD)
		return (FALSE);
	value = look_ahead->value;
	if (!ft_isalpha(*value) && *value != '_')
		return (FALSE);
	i = 1;
	while (value[i])
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

static void	options(t_list *token_list, t_token **look_ahead, t_command *cmd)
{
	t_token	*token;

	while (*look_ahead && (*look_ahead)->type == WORD)
	{
		token = initialize_token();
		token->type = (*look_ahead)->type;
		token->value = ft_strdup((*look_ahead)->value);
		get_next_token(token_list, look_ahead);
		ft_lstadd_back(&cmd->tokens, ft_lstnew(token));
	}
}

static void	command_name(t_list *token_list, t_token **look_ahead,
	t_command *cmd)
{
	t_token	*token;

	if (is_identifier(*look_ahead) == FALSE)
	{
		if (!errno)
			send_error("syntax error near unexpected token: ",
				(*look_ahead)->value, 1);
		errno = 42;
		return ;
	}
	token = initialize_token();
	token->type = (*look_ahead)->type;
	token->value = ft_strdup((*look_ahead)->value);
	get_next_token(token_list, look_ahead);
	ft_lstadd_back(&cmd->tokens, ft_lstnew(token));
}

static void	redirection(t_list *token_list, t_token **look_ahead,
	t_command *cmd)
{
	t_redir		*redir;

	while (*look_ahead && (*look_ahead)->type == REDIRECTION)
	{
		redir = initialize_redir(*look_ahead);
		get_next_token(token_list, look_ahead);
		if ((*look_ahead)->type != WORD)
		{
			if (!errno)
			{
				free(redir);
				if (*look_ahead == NULL)
					send_error("missing redirection identifier",
						"", 1);
				else
					send_error("syntax error near unexpected token: ",
						(*look_ahead)->value, 1);
			}
			errno = 42;
			return ;
		}
		redir->file = ft_strdup((*look_ahead)->value);
		ft_lstadd_back(&cmd->redirs, ft_lstnew(redir));
		get_next_token(token_list, look_ahead);
	}
}

t_command	*command(t_list *token_list, t_token **look_ahead)
{
	t_command	*cmd;

	cmd = initialize_cmd();
	redirection(token_list, look_ahead, cmd);
	command_name(token_list, look_ahead, cmd);
	redirection(token_list, look_ahead, cmd);
	options(token_list, look_ahead, cmd);
	redirection(token_list, look_ahead, cmd);
	if (errno)
		return (free_cmd(cmd), NULL);
	return (cmd);
}
