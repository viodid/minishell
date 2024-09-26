/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:02:59 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/01 19:40:31 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_aredigits(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
	}
	return (TRUE);
}

//TODO refactor code correctly when send_error is ready
//TODO exit from a child shouldn't print error
int	ft_exit(t_data *core, char **args, int cmd_nb)
{
	unsigned char	exitcode;

	if (!args[1])
		exitcode = core->errcode;
	else if (!args[2])
	{
		if (ft_aredigits(args[1]))
			exitcode = ft_atoi(args[1]);
		else
			exitcode = 2;
	}
	else if (args[2] && ft_aredigits(args[1]))
	{
		dprintf(2, "exit\n");
		dprintf(2, "Corresponding error1\n");
		core->errcode = 1;
		return (1);
	}
	else
		exitcode = 2;
	if (core->line->nbcommands == 1)
	{
		dprintf(2, "exit\n");
		if (exitcode && args[1])
			dprintf(2, "exit: %s: numeric argument required\n", args[1]);
	}
	// if (core->line->nbcommands == 1)
	// 	free_struct(core);
	exit(exitcode);
	// return (exitcode);
}
