/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:23:00 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/06/09 20:23:03 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO export builtin required to change PWD and OLDPWD env vars

int	cd(char *dest, t_data *core)
{
	int	retcode;

	retcode = chdir(dest);
	if (retcode)
	{
		printf("cd: %s: %s\n", strerror(errno), dest);
	}
	return (EXIT_SUCCESS);
}
