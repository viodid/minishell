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

//TODO refractor code correctly when send_error is ready
int	ft_exit(t_data *core, char **args)
{
	int				i;
	unsigned char	exitcode;
	(void)args;

	i = 0;
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
		printf("exit\n");
		printf("Corresponding error");
		core->errcode = 1;
		return (1);
	}
	else
		exitcode = 2;
	free_struct(core);
	printf("exit\n");
	if (exitcode)
		printf("Corresponding error");
	exit(exitcode);
}
