/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:07 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/03/22 18:27:10 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	minishell()
{
	char *str;

	str = readline("minishell >");
	if (!str)
		return (EXIT_FAILURE);
	else
		printf("%s\n", str);
	free(str);
	return (EXIT_SUCCESS);
}