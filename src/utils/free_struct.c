/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:12:21 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/09 20:48:48 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_token(void *cont)
{
	t_token	*token;

	token = (t_token *)cont;
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	free(cont);
}

void	free_redir(void *cont)
{
	t_redir	*redir;

	redir = (t_redir *)cont;
	if (redir->file)
	{
		free(redir->file);
		redir->file = NULL;
	}
	free(redir);
}

void	free_cmd(void *cont)
{
	t_command	*command;

	command = (t_command *)cont;
	if (command->redirs)
		ft_lstclear(&command->redirs, free_redir);
	if (command->tokens)
		ft_lstclear(&command->tokens, free_token);
}

void	free_var(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	free(var->key);
	free(var->value);
	free(var);
}

void	unlink_hdocs(t_line *line)
{
	t_list		*commands;
	t_command	*command;
	t_list		*redirs;
	t_redir		*redir;

	commands = line->cmds;
	while (commands && commands->content)
	{
		command = (t_command *)commands->content;
		redirs = command->redirs;
		while (redirs && redirs->content)
		{
			redir = (t_redir *)redirs->content;
			dprintf(2, "unlinking %s, type %i\n", redir->file, redir->type);
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

	hola("free_line");
	i = 0;
	unlink_hdocs(line);
	if (ft_lstsize(line->cmds))
		ft_lstclear(&line->cmds, &free_cmd);
	while (i < line->nbcommands)
		free(line->fds[i]);
	if (line->fds)
		free(line->fds);
	if (line->pids)
		free(line->pids);
}

void	free_struct(t_data *core)
{
	ft_lstclear(&core->env, free_var);
	if (core->line)
		free_line(core->line);
}
