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

//TODO protect allocations
int	update_pwd(t_data *core, char *oldpwd)
{
	char	*newcwd;
	char	*var;

	newcwd = getcwd(NULL, 0);
	var = ft_strjoin_f2("PWD=", newcwd);
	export(core, var);
	free(var);
	var = ft_strjoin_f2("OLDPWD=", oldpwd);
	export(core, var);
	free(var);
	return (EXIT_SUCCESS);
}

//TODO protect allocations
int	cd(t_data *core, char *dest)
{
	int		retcode;
	char	*oldpwd;
	t_var	*home;

	oldpwd = getcwd(NULL, 0);	
	if (!dest)
	{
		home = get_env(core, "HOME");
		if (!home)
		{
			printf("cdd: %s: %s\n", strerror(errno), dest);
			return(EXIT_FAILURE);
		}
		retcode = chdir(home->value);
	}
	else
		retcode = chdir(dest);
	if (retcode)
	{
		printf("cd: %s: %s\n", strerror(errno), dest);
		return (EXIT_FAILURE);
	}
	update_pwd(core, oldpwd);
	return (EXIT_SUCCESS);
}
