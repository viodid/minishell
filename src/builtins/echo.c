/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:29:44 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/26 20:00:30 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO contemplar -n -n -o
int	ft_echo(int option, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		i++;
	}
	if (!option)
		printf("\n");
	return (EXIT_SUCCESS);
}
