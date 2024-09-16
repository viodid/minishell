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
