/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:26:03 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/08 18:12:14 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_line	*initialize_line(void)
{
	t_line	*line;

	line = (t_line *) malloc(sizeof(t_line));
	if (!line)
		exit(EXIT_FAILURE);
	line->cmds = NULL;
	line->fds = NULL;
	line->pids = NULL;
	line->stdinbak = 0;
	return (line);
}

void *parser(t_data *core)
{
	t_line	*line;
	t_list	*token_list;

	token_list = lexer();
	if (errno || !token_list)
		return (NULL);
	line = initialize_line();
	line->cmds = descent_parser(token_list);
	ft_lstiter(line->cmds, &print_command);
	return (line);
}
