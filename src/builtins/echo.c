/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 17:29:44 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/29 21:04:40 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	has_option(char **args)
{
	int	i;
	int	j;

	i = 0;
	while (args[++i])
	{
		j = 0;
		if (!(args[i][j++] == '-'))
			return (i);
		while (args[i][j] == 'n')
			j++;
		if (args[i][j])
			return (i);
	}
	return (i);
}

int	ft_echo(char **args)
{
	int		i;
	char	nl;

	nl = '\n';
	i = has_option(args);
	if (i > 1)
		nl = 0;
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i + 1])
			printf(" ");
		i++;
	}
	printf("%c", nl);
	return (EXIT_SUCCESS);
}
