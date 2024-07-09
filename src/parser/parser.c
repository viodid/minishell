/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:19:02 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/05/27 18:19:05 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_element(void *content)
{
	printf("%s\n", (char *)content);
}

t_command	*parse_command(char *str)
{
	int			i;
	char		**split;
	t_list		*lst;
	t_command	*cmd;

	i = -1;
	lst = NULL;
	split = ft_split(str, ' ');
	cmd = ft_calloc(sizeof(t_command), 1);
	while (split[++i])
	{
		ft_lstadd_back(&lst, ft_lstnew(split[i]));
	}
	ft_lstiter(lst, &print_element);
	cmd->tokens = lst;
	// cmd->i_cmd = pos[0];
	// cmd->i_outredir = pos[1];
	return (cmd);
}

int	temp_parser(t_data *core, char **cmds)
{
	int			i;
	t_command	*command;

	i = 0;
	while (cmds[i])
	{
		command = parse_command(cmds[i]);
		ft_lstadd_back(&core->cmds, ft_lstnew(command));
		i++;
	}
	return (EXIT_SUCCESS);
}
