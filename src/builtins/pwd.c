/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 18:39:26 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/05/31 18:39:28 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd(t_data *core)
{
	char *path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		path = ft_getenv("PWD", core->envp);
		if (!path)
		{
			perror("pwd");
			return ;
		}
		printf("%s i\n", path);
		return ;
	}
	printf("%s\n", path);
	free(path);
}
