/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:22:43 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/11/26 20:20:50 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	handle_interactive_signals(int signum)
{
	write(STDERR_FILENO, "\n", 1);
	rl_replace_line("", FALSE);
	rl_on_new_line();
	rl_redisplay();
	(void) signum;
}

static void	handle_non_interactive_signals(int signum)
{
	if (signum == SIGINT)
	{
		ft_putendl_fd("\n", 2);
		signum = 130;
	}
	else if (signum == SIGQUIT)
		ft_putendl_fd("Quit\n", 5);
}

void	signal_handler(t_shell_mode mode)
{
	if (mode == INTER)
	{
		signal(SIGINT, handle_interactive_signals);
		signal(SIGQUIT, SIG_IGN);
	}
	else if (mode == NONIN)
	{
		signal(SIGINT, handle_non_interactive_signals);
		signal(SIGQUIT, handle_non_interactive_signals);
	}
}
