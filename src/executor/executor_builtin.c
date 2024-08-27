/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 20:48:47 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/27 21:07:39 by kde-la-c         ###   ########.fr       */
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
		ft_strncmp(command, "cd", 3)
		|| ft_strncmp(command, "echo", 5)
		|| ft_strncmp(command, "env", 4)
		|| ft_strncmp(command, "exit", 5)	//parent
		|| ft_strncmp(command, "export", 7)	//parent
		|| ft_strncmp(command, "pwd", 4)
		|| ft_strncmp(command, "unset", 6)	//parent
	);
}

int	exec_builtin(t_data *core, t_command *cmd)
{
	int		retcode;
	char	*command;
	(void)core;
	(void)cmd;

	command = ((t_token *)cmd->tokens->content)->value;
	if (!ft_strncmp(command, "cd", 3))
		retcode = ft_cd(core, cmd->tokens->content);
	return (retcode);
}

