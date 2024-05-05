/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:07 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/03/22 18:27:10 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main()
{
	char	*str;

	while (1)
	{
		str = readline("minishell >");
		printf("%s\n", str);
	}
	return (EXIT_SUCCESS);
}
