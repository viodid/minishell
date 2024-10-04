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

// void	do_exit(char *err, char *errarg, unsigned char errcode)
// {
// 	if (!err && !errarg)
// 	{
// 		dprintf((errcode && 1) + 1, "exit\n");
// 		exit(errcode);
// 	}
// 	else

// }

//TODO refactor code correctly when send_error is ready
//TODO exit from a child shouldn't print error
int	ft_exit(t_data *core, char **args, int cmd_nb)
{
	unsigned char	exitcode;

	if (!args[1])
		exit(EXIT_SUCCESS);
	else if (!args[2] && ft_aredigits(args[1]))
		exit(ft_atoi(args[1]));
	else if (!args[2] && !ft_aredigits(args[1]))
	{
		dprintf(2, "exit");
	}
	exit(exitcode);
}
