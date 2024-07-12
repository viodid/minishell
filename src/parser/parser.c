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

/* t_command	*parse_command(char *str)
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
	ft_lstiter(lst, &print_str);
	cmd->tokens = lst;
	return (cmd);
} */

//TODO finish command parser according to structures
t_command	*parse_command(char *str)
{
	int			i;
	int			j;
	char		**tokens;
	t_command	*ret;
	t_redir		*redir;
	t_token		*token;

	ret = ft_calloc(1, sizeof(t_command));
	i = 0;
	j = 0;
	tokens = ft_split(str, ' ');
	while (tokens[i])
	{
		// get rid of first redirections
		if (j == 0 && !ft_strncmp(tokens[i], "<", 1))
		{
			redir = ft_calloc(1, sizeof(t_redir));
			if (!ft_strncmp(tokens[i], "<<", 2))
				redir->type = HEREDOC;
			else
				redir->type = INPUT;
			redir->file = tokens[++i];
			ft_lstadd_back(&ret->redirs, ft_lstnew(redir));
		}
		else
			j = 1;


		if (j == 1)
		{
			token = ft_calloc(1, sizeof(t_token));
			token->value = tokens[i];
			token->type = ARGUMENT;
		}
		if (!ft_strncmp(tokens[i + 1], ">", 1))
		{
			
		}


		i++;
	}
	return (NULL);
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
