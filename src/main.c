/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:29:17 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/10/27 19:46:50 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	signal_handler(int signum, siginfo_t *info, void *context);

uint8_t	curr_signal;

int	main(int argc, char **argv, char **envp)
{
	int					i;
	int					retcode;
	t_data				core;
	struct sigaction	act;
	(void)argc;

	// Signals
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &signal_handler;

	if (init_core(&core, argv, envp))
		return (ft_fdprintf(2, "minishell: allocation error\n"), EXIT_FAILURE);
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
		core.line = NULL;
		if (retcode)
			return (free_struct(&core), retcode);
	}
}

/*
 * By the absent of the SIGQUIT handler, SIGQUIT is implicitly ignored.
*/
static void	signal_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;

	if (signum == SIGHUP)
		ft_printf("SIGHUP\n");
	if (signum == SIGINT)
	{
		curr_signal = SIGINT;
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", FALSE);
		rl_on_new_line();
		rl_redisplay();
	}
}
