/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:48:47 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/31 23:57:57 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	isbuiltin(char *cmdpath)
{
	return (
		!ft_strncmp(cmdpath, "cd", 3)
		|| !ft_strncmp(cmdpath, "echo", 5)
		|| !ft_strncmp(cmdpath, "env", 4)
		|| !ft_strncmp(cmdpath, "exit", 5)
		|| !ft_strncmp(cmdpath, "export", 7)
		|| !ft_strncmp(cmdpath, "pwd", 4)
		|| !ft_strncmp(cmdpath, "unset", 6)
	);
}

int	exec_builtin(t_data *core, char *cmdpath, char **args, int is_exit)
{
	int		retcode;

	//TODO get rid of first if when expansion is complete
	if (!ft_strncmp(cmdpath, "pwd", 4))
		retcode = ft_pwd(core);
	else if (!ft_strncmp(cmdpath, "cd", 3))
		retcode = ft_cd(core, args);
	else if (!ft_strncmp(cmdpath, "echo", 5))
		retcode = ft_echo(args);
	else if (!ft_strncmp(cmdpath, "env", 4))
		retcode = ft_env(core);
	else if (!ft_strncmp(cmdpath, "exit", 5))
	{
		retcode = ft_exit(core, args, !is_exit);
		free_struct(core);
		exit(retcode);
	}
	else if (!ft_strncmp(cmdpath, "export", 7))
		retcode = ft_export(core, args);
	else if (!ft_strncmp(cmdpath, "unset", 6))
		retcode = ft_unset(core, args);
	if (is_exit)
		exit(retcode);
	return (retcode);
}

