/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:26:03 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/16 19:21:20 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static	t_list	*descent_parser(t_list *token_list);

void	parser(t_data *core)
{
	t_list	*token_list;

	token_list = lexer();
	ft_lstiter(token_list, &print_tokens);
	if (errno || !token_list)
		return ;
	core->line = initialize_line();
	core->line->cmds = descent_parser(token_list);
	core->line->pids = ft_calloc(ft_lstsize(core->line->cmds), sizeof(int));
	ft_lstclear(&token_list, &free_token);
	ft_lstiter(core->line->cmds, &print_command);
	execute_expansions(core);
	ft_lstiter(core->line->cmds, &print_command);
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

static	t_list	*descent_parser(t_list *token_list)
{
	t_list	*cmds;
	t_token	*look_ahead;

	look_ahead = (t_token *)token_list->content;
	cmds = full_command(token_list, &look_ahead);
	if (errno)
	{
		ft_lstclear(&cmds, &free_cmd);
		cmds = NULL;
	}
	return (cmds);
}
