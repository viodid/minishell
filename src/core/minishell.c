/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:07 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/10/15 19:09:10 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	extra_parsings(t_data *core)
{
	//TODO (dyunta): quitar el parsing para el export
	int	i;

	i = 0;
	if (core->line)
	{
		core->line->nbcommands = 0;
		if (core->line->cmds)
			core->line->nbcommands = ft_lstsize(core->line->cmds);
		if (core->line->nbcommands > 1)
		{
			core->line->fds = ft_calloc(core->line->nbcommands, sizeof(int *));
			while (i < core->line->nbcommands)
				core->line->fds[i++] = ft_calloc(2, sizeof(int));
		}
	}
}

 int	minishell(t_data *core)
 {
 	int			retcode;
 	char		**cmds;

 	errno = 0;
 	parser(core);
 	if (errno)
 		return(EXIT_FAILURE); // TODO: change to EXIT_SUCCESS
	// retcode = executor(core);
 	retcode = 0;
 	return (retcode);
}
