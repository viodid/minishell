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

// int	reset_stdfds(t_data *core, t_fds fds, t_list *redirs)
// {
// 	(void)redirs;
// 	fprintf(stderr, "outbak %i\n", core->line->stdoutbak);
// 	if (core->line->stdinbak && fds.stdfdin == STDIN_FILENO)
// 	{
// 		if (dup2(core->line->stdinbak, fds.stdfdin))
// 			return (perror("restore stdin"), -1);
// 	}
// 	if (core->line->stdoutbak && fds.stdfdout == STDOUT_FILENO)
// 	{
// 		if (dup2(core->line->stdoutbak, fds.stdfdin))
// 			return (perror("restore stdout"), fprintf(stderr, ">>%i\n", errno), -1);
// 	}
// 	return (EXIT_SUCCESS);
// }

// int	close_fds(t_data *core, t_pipe_fds fds)
// {
// 	if (fds == READ_FD)
// 		return (close(core->line->fds[READ_FD]));
// 	else if (fds == WRITE_FD)
// 		return (close(core->line->fds[WRITE_FD]));
// 	else if (fds == BOTH_FDS)
// 	{
// 		if (close(core->line->fds[READ_FD]))
// 			return (errno);
// 		if (close(core->line->fds[WRITE_FD]))
// 			return (errno);
// 	}
// 	return (EXIT_SUCCESS);
// }

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
	return (EXIT_SUCCESS);
}
