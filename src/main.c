/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:29:17 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/16 01:58:18 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	signal_handler(int signum, siginfo_t *info, void *context);

int	main(int argc, char **argv, char **envp)
{
	int					i;
	int					retcode;
	t_data				core;
	struct sigaction	act;

	// Signals
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;

	if (init_core(&core, argv, envp))
		return (ft_fdprintf(2, "minishell: allcoation error\n"), EXIT_FAILURE);
	while (1)
	{
		sigaction(SIGINT, &act, NULL);
		sigaction(SIGQUIT, &act, NULL);
		sigaction(SIGHUP, &act, NULL);
		retcode = minishell(&core);
		while (1)
		{
			i = waitpid(-1, NULL, 0);
			if (i < 0)
				break ;
		}
		free_line(core.line);
		if (retcode)
			return (free_struct(&core), retcode);
	}
	free_struct(&core);
	return (retcode);
}

static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	if (signum == SIGHUP)
		ft_printf("SIGHUP\n");
	if (signum == SIGINT)
		ft_printf("SIGINT\n");
	if (signum == SIGQUIT)
		ft_printf("SIGQUIT\n");
}
