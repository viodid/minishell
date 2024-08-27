/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:48:47 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/28 00:25:58 by kde-la-c         ###   ########.fr       */
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

	if (!ft_strncmp(path, "cd", 3))
		retcode = ft_cd(core, args[1]); //TODO change prototypes to get execve like params
	return (retcode);
}

