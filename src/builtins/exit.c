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
	if (str[0] == '-' || str[0] == '+')
		i++;
	while (str[++i])
	{
		if (!ft_isdigit(str[i]))
			return (FALSE);
	}
	return (TRUE);
}

void	do_exit(char *err, char *errarg, unsigned char errcode)
{
	ft_fdprintf(2, "exit\n");
	if (err)
	{
		if (errarg)
			ft_fdprintf(2, "minishell: exit: %s: %s\n", errarg, err);
		else
		{
			ft_fdprintf(2, "minishell: exit: %s\n", err);
			return ;
		}
	}
	exit(errcode);
}

//TODO refactor code correctly when send_error is ready
//TODO exit from a child shouldn't print error
int	ft_exit(char **args)
{
	if (!args[1])
		do_exit(NULL, NULL, 0);
	else if (!args[2] && ft_aredigits(args[1]))
		do_exit(NULL, NULL, ft_atoi(args[1]));
	else if (!ft_aredigits(args[1]))
		do_exit("numeric argument required", args[1], 2);
	else if (ft_aredigits(args[1]))
		do_exit("too many arguments", NULL, 1);
	return (EXIT_FAILURE);
}
