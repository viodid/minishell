/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:23:00 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/29 21:15:07 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	update_pwd(t_list **env, char *oldpwd)
int	update_pwd(t_data *core, char *oldpwd)
{
	char	*newcwd;
	char	*var;

	newcwd = getcwd(NULL, 0);
	var = ft_strjoin_f2("PWD=", newcwd);
	if (!var)
		return (EXIT_FAILURE);
	ft_export(core, var);
	free(var);
	var = ft_strjoin_f2("OLDPWD=", oldpwd);
	if (!var)
		return (EXIT_FAILURE);
	ft_export(core, var);
	free(var);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_data *core, char **args)
{
	int		retcode;
	char	*oldpwd;
	t_var	*home;

	if (args[2])
		return (perror("cd: too many arguments"), errno);
	oldpwd = getcwd(NULL, 0);
	if (!args[1])
	{
		home = get_env(core, "HOME");
		if (!home)
		{
			printf("cd: %s: %s\n", strerror(errno), args[1]);
			return(errno);
		}
		retcode = chdir(home->value);
	}
	else
		retcode = chdir(args[1]);
	if (retcode)
	{
		printf("cd: %s: %s\n", strerror(errno), args[1]);
		return (errno);
	}
	update_pwd(core, oldpwd);
	return (EXIT_SUCCESS);
}
