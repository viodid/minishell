/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:00:57 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/06 21:00:58 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	close_fds(t_data *core, t_pipe_fds fds)
{
	if (fds == READ_FD)
		return (close(core->line->fds[READ_FD]));
	else if (fds == WRITE_FD)
		return (close(core->line->fds[WRITE_FD]));
	else if (fds == BOTH_FDS)
	{
		if (close(core->line->fds[READ_FD]))
			return (errno);
		if (close(core->line->fds[WRITE_FD]))
			return (errno);
	}
	return (EXIT_SUCCESS);
}

int	set_fds(t_fds *fds, t_data *core, int cmd_nb)
{
	if (pipe(core->line->fds))
		return (perror("piping"), errno);
	if (core->line->nbcommands == 1)
	{
		fds->stdfdin = STDIN_FILENO;
		fds->stdfdout = STDOUT_FILENO;		
	}
	else if (cmd_nb == 0 && core->line->nbcommands > 1)
	{
		fds->stdfdin = STDIN_FILENO;
		fds->stdfdout = core->line->fds[WRITE_FD];
	}
	else if (cmd_nb && cmd_nb == core->line->nbcommands - 1)
	{
		fds->stdfdin = core->line->fds[READ_FD];
		fds->stdfdout = STDOUT_FILENO;
	}
	else
	{
		fds->stdfdin = core->line->fds[READ_FD];
		fds->stdfdout = core->line->fds[WRITE_FD];
	}
	return (EXIT_SUCCESS);
}
