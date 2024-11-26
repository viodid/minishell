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

int	exec_builtin(t_data *core, char *cmdpath, char **args)
{
	if (!ft_strncmp(cmdpath, "pwd", 4))
		core->errcode = ft_pwd(core);
	else if (!ft_strncmp(cmdpath, "cd", 3))
		core->errcode = ft_cd(core, args);
	else if (!ft_strncmp(cmdpath, "echo", 5))
		core->errcode = ft_echo(args);
	else if (!ft_strncmp(cmdpath, "env", 4))
		core->errcode = ft_env(core);
	else if (!ft_strncmp(cmdpath, "exit", 5))
		core->errcode = ft_exit(core, args, core->line->nbcommands > 1);
	else if (!ft_strncmp(cmdpath, "export", 7))
		core->errcode = ft_export(core, args);
	else if (!ft_strncmp(cmdpath, "unset", 6))
		core->errcode = ft_unset(core, args);
	if (core->line->nbcommands > 1)
		exit(core->errcode);
	return (core->errcode);
}
