/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:01:31 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/16 19:01:32 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_piperedir(t_data *core, t_command *command, t_fds fds, int cmd_nb)
{
	int	**pipes;

	if (core->line->nbcommands < 2)
		return (EXIT_SUCCESS);
	pipes = core->line->fds;
	if (cmd_nb == 0)
	{
		close(pipes[0][READ_FD]);
		dup2(pipes[0][WRITE_FD], STDOUT_FILENO);
		close(pipes[0][WRITE_FD]);
	}
	else if (cmd_nb < core->line->nbcommands - 1)
	{
		close(pipes[cmd_nb][READ_FD]);
		dup2(pipes[cmd_nb - 1][READ_FD], STDIN_FILENO);
		close(pipes[cmd_nb - 1][READ_FD]);
		dup2(pipes[cmd_nb][WRITE_FD], STDOUT_FILENO);
		close(pipes[cmd_nb][WRITE_FD]);
	}
	else if (cmd_nb == core->line->nbcommands - 1)
	{
		dup2(pipes[cmd_nb - 1][READ_FD], STDIN_FILENO);
		close(pipes[cmd_nb - 1][READ_FD]);
	}
	return (EXIT_SUCCESS);
}

int	close_parent_pipes(t_data *core, int cmd_nb)
{
	int	**pipes;

	if (core->line->nbcommands < 2)
		return (EXIT_SUCCESS);
	pipes = core->line->fds;
	if (cmd_nb == 0)
		close(pipes[0][WRITE_FD]);
	else if (cmd_nb < core->line->nbcommands - 1)
	{
		close(pipes[cmd_nb - 1][READ_FD]);
		close(pipes[cmd_nb][WRITE_FD]);
	}
	else if (cmd_nb == core->line->nbcommands - 1)
		close(pipes[cmd_nb - 1][READ_FD]);
	return (EXIT_SUCCESS);
}

int	init_pipes(t_data *core)
{
	int	i;

	i = 0;
	while (i < core->line->nbcommands)
	{
		if (pipe(core->line->fds[i++]))
			return (perror("pipes"), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
