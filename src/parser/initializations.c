/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:26:12 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/09 21:48:20 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	get_next_token(t_list *token_list, t_token **look_ahead)
{
	while (token_list->next)
	{
		if (token_list->content == *look_ahead)
		{
			*look_ahead = token_list->next->content;
			return ;
		}
		token_list = token_list->next;
	}
	*look_ahead = NULL;
}

t_redir	*initialize_redir(t_token *token)
{
	t_redir	*redir;

	redir = (t_redir *) malloc(sizeof(t_redir));
	if (!redir)
		exit(EXIT_FAILURE);
	if (ft_strncmp(token->value, "<", 2) == 0)
		redir->type = INPUT;
	else if (ft_strncmp(token->value, ">", 2) == 0)
		redir->type = OUTPUT;
	else if (ft_strncmp(token->value, ">>", 3) == 0)
		redir->type = APPEND;
	else if (ft_strncmp(token->value, "<<", 3) == 0)
		redir->type = HEREDOC;
	else
		exit(EXIT_FAILURE);
	redir->file = NULL;
	redir->token_type = token->type;
	return (redir);
}

t_token	*initialize_identifier(void)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->value = NULL;
	token->type = -1;
	return (token);
}

t_command	*initialize_cmd(void)
{
	t_command	*cmd;

	cmd = (t_command *) malloc(sizeof(t_command));
	if (!cmd)
		exit(EXIT_FAILURE);
	cmd->tokens = NULL;
	cmd->redirs = NULL;
	ft_memset(&cmd->fds, -1, sizeof(t_fds));
	return (cmd);
}

t_line	*initialize_line(void)
{
	t_line	*line;

	line = (t_line *) malloc(sizeof(t_line));
	if (!line)
		exit(EXIT_FAILURE);
	line->cmds = NULL;
	line->fds = NULL;
	line->pids = NULL;
	return (line);
}