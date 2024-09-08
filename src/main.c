/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:29:17 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/07 11:22:43 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	*core;
	(void)argc;
	(void)argv;
	(void)i;

	core = ft_calloc(1, sizeof(t_data));
	core->env = set_env(envp);
	core->line.cmds = NULL;
	while (1)
	{
		i = minishell(core);
		if (i)
		{
			free_struct(core);
			return (i);
		}
	}
	free_struct(core);
	return (EXIT_SUCCESS);
}
