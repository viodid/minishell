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

volatile sig_atomic_t	g_signum;

static void	handle_interactive_signals(int g_signum)
{
	g_signum = 130;
	write(STDOUT_FILENO, "\n", 1);
	rl_replace_line("", FALSE);
	rl_on_new_line();
	rl_redisplay();
	(void) g_signum;
}

static void	handle_non_interactive_signals(int g_signum)
{
	if (g_signum == SIGINT)
	{
		ft_putendl_fd("\n", 2);
		g_signum = 130;
	}
	else if (g_signum == SIGQUIT)
		ft_putendl_fd("Quit\n", 5);
}

void	signal_handler(t_shell_mode mode)
{
	g_signum = 0;
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
