/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 21:00:57 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/09 19:05:19 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	save_stdfds(t_data *core)
{
	core->sv_stdin = dup(STDIN_FILENO);
	if (core->sv_stdin == -1)
		return (perror("save stdin"), EXIT_FAILURE);
	core->sv_stdout = dup(STDOUT_FILENO);
	if (core->sv_stdout == -1)
		return (perror("save stdout"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	reset_stdfds(t_data *core)
{
	if (dup2(core->sv_stdin, STDIN_FILENO) == -1)
		return(perror("restore input"), EXIT_FAILURE);
	if (dup2(core->sv_stdout, STDOUT_FILENO) == -1)
		return(perror("restore output"), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	set_fds(t_fds *fds, t_data *core, int cmd_nb)
{
	if (core->line->nbcommands == 1)
	{
		fds->stdfdin = STDIN_FILENO;
		fds->stdfdout = STDOUT_FILENO;
	}
	else if (cmd_nb == 0 && core->line->nbcommands > 1)
	{
		fds->stdfdin = STDIN_FILENO;
		fds->stdfdout = core->line->fds[cmd_nb][WRITE_FD];
	}
	else if (cmd_nb && cmd_nb == core->line->nbcommands - 1)
	{
		fds->stdfdin = core->line->fds[cmd_nb - 1][READ_FD];
		fds->stdfdout = STDOUT_FILENO;
	}
	else
	{
		fds->stdfdin = core->line->fds[cmd_nb - 1][READ_FD];
		fds->stdfdout = core->line->fds[cmd_nb][WRITE_FD];
	}
	fds->fdin = fds->stdfdin;
	fds->fdout = fds->stdfdout;
	return (EXIT_SUCCESS);
}
