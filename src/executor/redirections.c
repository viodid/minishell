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

int	redirect_files(t_command *command, t_fds *fds)
{
	if (hasinput(command->redirs))
	{
		fds->fdin = redirect_infile((t_list *)command->redirs, *fds,
				(command->tokens && 1));
		if (fds->fdin == -1)
			return (perror("post redirect"), -1);
	}
	if (hasoutput(command->redirs))
	{
		fds->fdout = redirect_outfile((t_list *)command->redirs, *fds);
		if (fds->fdout == -1)
			return (perror("post redirect"), -1);
	}
	return (EXIT_SUCCESS);
}
