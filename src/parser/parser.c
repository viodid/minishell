/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:26:03 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/07 19:04:14 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	initialize_line(t_line *line)
{
	line->cmds = NULL;
	line->fds = NULL;
	line->pids = NULL;
	line->stdinbak = 0;
}

t_line	parser(void)
{
	t_line	line;
	t_list	*token_list;

	initialize_line(&line);
	token_list = lexer();
	line.cmds = RDP(token_list);
	ft_lstiter(line.cmds, &print_command);
	return (line);
}
