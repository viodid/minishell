/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:29:17 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/29 19:48:28 by kde-la-c         ###   ########.fr       */
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
	core->line.cmds = NULL;
	while (1)
	{
		retcode = minishell(core);
		while (1)
		{
			i = waitpid(-1, NULL, 0);
			if (i < 0)
				break ;
		}
		if (retcode)
			return (free_struct(core), retcode);
	}
	free_struct(core);
	return (retcode);
}
