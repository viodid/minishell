/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:19:02 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/09 20:47:04 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// temp command parser, divides a command into redirections and arguments
t_command	*parse_command(char *str)
{
	int			i;
	char		**tokens;
	t_command	*ret;
	t_redir		*redir;
	t_token		*token;

	ret = ft_calloc(1, sizeof(t_command));
	if (!ret)
		perror("tmp parser");
	i = 0;
	tokens = ft_split(str, ' ');
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '<') || ft_strchr(tokens[i], '>'))
		{
			redir = ft_calloc(1, sizeof(t_redir));
			if (!redir)
				perror("tmp parser");
			redir->type = HEREDOC + (!ft_strncmp(tokens[i], "<", 2) && 1)
						+ (!ft_strncmp(tokens[i], ">", 1) && 1) * 2
						+ (!ft_strncmp(tokens[i], ">>", 2) && 1);
			i++;
			redir->file = tokens[i];
			ft_lstadd_back(&ret->redirs, ft_lstnew(redir));
		}
		i++;
	}
	i = 0;
	while (tokens[i])
	{
		if (!(ft_strchr(tokens[i], '<') || ft_strchr(tokens[i], '>'))
		&& (!i || (i && !(ft_strchr(tokens[i - 1], '<') || ft_strchr(tokens[i - 1], '>')))))
		{
			token = ft_calloc(1, sizeof(t_token));
			if (!token)
				perror("tmp parser");
			token->value = tokens[i];
			token->type = IDENTIFIER + (ret->tokens && 1);
			ft_lstadd_back(&ret->tokens, ft_lstnew(token));
		}
		i++;
	}
	ft_memset(&ret->fds, -1, sizeof(t_fds));
	free(tokens);
	return (ret);
}

int	tmp_parser(t_data *core, char **cmds)
{
	int			i;
	int			j;
	t_command	*command;

	i = 0;
	j = 0;
	core->line = ft_calloc(1, sizeof(t_line));
	if (!core->line)
		return (EXIT_FAILURE);
	core->line->cmds = NULL;
	while (cmds[i])
	{
		command = parse_command(cmds[i]);
		ft_lstadd_back(&core->line->cmds, ft_lstnew(command));
		i++;
	}
	if (i)
		core->line->pids = ft_calloc(i, sizeof(int));
	else
		core->line->pids = NULL;
	core->line->nbcommands = i;
	core->line->fds = ft_calloc(i, sizeof(int *));
	while (j < i)
		core->line->fds[j++] = ft_calloc(2, sizeof(int));
	return (EXIT_SUCCESS);
}
