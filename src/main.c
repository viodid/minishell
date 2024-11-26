/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:29:17 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/11/26 17:09:45 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	signal_handler(int signum);


int	main(int argc, char **argv, char **envp)
{
	int					retcode;
	t_data				core;
	(void)argc;

	if (init_core(&core, argv, envp))
		return (ft_fdprintf(2, "minishell: allocation error\n"), EXIT_FAILURE);
	while (1)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, SIG_IGN);
		retcode = minishell(&core);
		free_line(core.line);
		core.line = NULL;
		if (retcode)
			return (free_struct(&core), retcode);
	}
}
