/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 20:23:00 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/31 23:35:27 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	update_pwd(t_data *core, char *oldpwd)
{
	char	*newcwd;
	char	*var;

	newcwd = getcwd(NULL, 0);
	var = ft_strjoin_f2("PWD=", newcwd);
	if (!var)
		return (EXIT_FAILURE);
	export_single(core, var);
	free(var);
	var = ft_strjoin("OLDPWD=", oldpwd);
	if (!var)
		return (EXIT_FAILURE);
	export_single(core, var);
	free(var);
	return (EXIT_SUCCESS);
}

char	*get_oldpwd(t_data *core)
{
	char	*ret;
	t_var	*var;

	var = get_env(core, "OLDPWD");
	if (var && var->value)
		return (var->value);
	ret = getcwd(NULL, 0);
	if (!ret)
		return (NULL);
	return (ret);
}

int	access_newcwd(char *path)
{
	int		ret;
	char	*oldpwd;
	char	*newpwd;

	if (path[0] == '/')
		return (access(path, F_OK));
	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (EXIT_FAILURE);
	newpwd = ft_strjoin_f1(oldpwd, "/");
	if (!newpwd)
		return (EXIT_FAILURE);
	newpwd = ft_strjoin_f1(newpwd, path);
	if (!newpwd)
		return (EXIT_FAILURE);
	ret = access(newpwd, F_OK);
	return (free(newpwd), ret);
}

int	ft_cd(t_data *core, char **args)
{
	char	*oldpwd;
	t_var	*home;

	if (args[1] && args[2])
		return (ft_fdprintf(2, "cd: too many arguments\n"), EXIT_FAILURE);
	oldpwd = get_oldpwd(core);
	if (!args[1])
	{
		home = get_env(core, "HOME");
		if (!home)
			return (ft_fdprintf(2, "cd: HOME not set\n"), errno);
		if (chdir(home->value))
			return (ft_fdprintf(2, "cd :"), perror(home->value), errno);
	}
	else
	{
		if (access_newcwd(args[1]))
			perror(args[1]);
		if (chdir(args[1]))
			return (errno);
	}
	update_pwd(core, oldpwd);
	return (EXIT_SUCCESS);
}
