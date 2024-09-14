/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:29:17 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/14 17:42:12 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		retcode;
	t_data	*core;
	(void)argc;
	(void)argv;
	(void)i;

	core = ft_calloc(1, sizeof(t_data));
	core->env = set_env(envp);
	core->errcode = 0;
	while (1)
	{
		retcode = minishell(core);
		while (1)
		{
			i = waitpid(-1, NULL, 0);
			if (i < 0)
				break ;
		}
		// TODO: handle frees better
//		free_line(core->line);
		if (retcode)
			return (free_struct(core), retcode);
	}
	free_struct(core);
	return (retcode);
}
