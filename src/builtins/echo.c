/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:29:44 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/05/27 17:29:48 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO take multiple arguments and print them separated by a single space
// int	ft_echo(int option, char **args)
int	ft_echo(int option, char *str)
{
	printf("%s", str);
	if (!option)
		printf("\n");
	return (EXIT_SUCCESS);
}
