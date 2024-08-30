/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:48:47 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/30 19:24:17 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	isbuiltin(t_command *cmd)
{
	char	*command = "";

	if (cmd->tokens)
		command = ((t_token *)cmd->tokens->content)->value;
	else
		return (FALSE);
	return (
		ft_strncmp(command, "cd", 3)		//parent
		|| ft_strncmp(command, "echo", 5)
		|| ft_strncmp(command, "env", 4)	//parent ????
		|| ft_strncmp(command, "exit", 5)	//parent
		|| ft_strncmp(command, "export", 7)	//parent
		|| ft_strncmp(command, "pwd", 4)
		|| ft_strncmp(command, "unset", 6)	//parent
	);
}

int	exec_builtin(t_data *core, char *path, char **args, char **envp)
{
	int		retcode;
	(void)core;
	(void)envp;
	// print_execve(path, args, envp);

	if (!ft_strncmp(path, "pwd", 4))
		retcode = ft_pwd(core);
	else if (!ft_strncmp(path, "cd", 3))
		retcode = ft_cd(core, args);
	else if (!ft_strncmp(path, "echo", 5))
		retcode = ft_echo(args);
	else if (!ft_strncmp(path, "env", 4))
		retcode = ft_env(core);
	else if (!ft_strncmp(path, "exit", 5))
		retcode = ft_exit(core, args);
	else if (!ft_strncmp(path, "export", 7))
		retcode = ft_export(core, args);
	return (retcode);
}

