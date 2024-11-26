/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:22:43 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/11/26 17:55:27 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

volatile sig_atomic_t	g_signal;

static void	signal_handler(t_shell_mode mode)
{
	if (mode == INTER)
	{
		write(STDOUT_FILENO, "\n", 1);
		rl_replace_line("", FALSE);
		rl_on_new_line();
		rl_redisplay();
	}
	else if (mode == NONIN)
	{
		printf("NONIN\n");
	}
	else if (mode == HERED)
	{
		printf("HERED\n");
	}
}
