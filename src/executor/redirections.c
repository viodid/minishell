/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:58:38 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/16 18:58:41 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	do_fileredir(t_command *command, t_fds fds)
{
	if (hasinput(command->redirs) && dup2(fds.fdin, STDIN_FILENO) == -1)
		return (EXIT_FAILURE);
	if (hasoutput(command->redirs) && dup2(fds.fdout, STDOUT_FILENO) == -1)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	get_redirs(t_command *command, t_fds *fds)
{
	if (hasinput(command->redirs))
	{
		fds->fdin = get_infiles((t_list *)command->redirs, fds,
				(command->tokens && 1));
		if (fds->fdin == -1)
			return (EXIT_FAILURE);
	}
	if (hasoutput(command->redirs))
	{
		fds->fdout = get_outfiles((t_list *)command->redirs, fds);
		if (fds->fdout == -1)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
