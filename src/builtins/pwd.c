/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:39:26 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/30 20:56:42 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_pwd(t_data *core) //TODO cuidado con imprimir un PWD que no exista con lo de rm ../../test
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		path = get_env(core, "PWD")->value;
		if (!path)
		{
			perror("pwd");
			return (EXIT_FAILURE);
		}
		printf("%s\n", path);
		return (EXIT_SUCCESS);
	}
	printf("%s\n", path);
	free(path);
	return (EXIT_SUCCESS);
}
