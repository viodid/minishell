/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:12:21 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/14 14:09:14 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_var(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	free(var->key);
	if (var->value)
		free(var->value);
	free(cont);
}

static void	unlink_hdocs(t_line *line)
{
	t_list		*commands;
	t_command	*command;
	t_list		*redirs;
	t_redir		*redir;

	if (!line || !line->cmds)
		return ;
	commands = line->cmds;
	while (commands && commands->content)
	{
		command = (t_command *)commands->content;
		redirs = command->redirs;
		while (redirs && redirs->content)
		{
			redir = (t_redir *)redirs->content;
			if (redir->type == H_INPUT)
			{
				unlink(redir->file);
				break ;
			}
			redirs = redirs->next;
		}
		commands = commands->next;
	}
}

void	free_line(t_line *line)
{
	int	i;

	if (!line)
		return ;
	i = 0;
	unlink_hdocs(line);
	if (line->cmds && ft_lstsize(line->cmds))
		ft_lstclear(&line->cmds, free_cmd);
	while (i < line->nbcommands && line->fds && line->fds[i])
	{
		if (line->fds[i][READ_FD] > 2)
			close(line->fds[i][READ_FD]);
		if (line->fds[i][WRITE_FD] > 2)
			close(line->fds[i][WRITE_FD]);
		free(line->fds[i++]);
	}
	if (line->fds)
		free(line->fds);
	if (line->pids)
		free(line->pids);
	free(line);
}

void	free_struct(t_data *core)
{
	ft_lstclear(&core->env, &free_var);
	if (core->line)
		free_line(core->line);
	if (core->sv_stdin > 2)
		close(core->sv_stdin);
	if (core->sv_stdout > 2)
		close(core->sv_stdout);
}
