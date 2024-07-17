/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/05/27 18:18:42 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	isbuiltin(t_command *cmd)
{
	char	*command;

	command = ((t_token *)cmd->tokens->content)->value;
	return (
		ft_strncmp(command, "cd", 3)
		|| ft_strncmp(command, "echo", 5)
		|| ft_strncmp(command, "env", 4)
		|| ft_strncmp(command, "exit", 5)
		|| ft_strncmp(command, "export", 7)
		|| ft_strncmp(command, "pwd", 4)
		|| ft_strncmp(command, "unset", 6)
	);
}

int	run_single(t_command *command, t_list *env)
{
	int	errcode;

	errcode = redirect((t_list *)command->redirs);
	//TODO make execution after redirection
}

int	executor(t_data *core)
{
	int		errcode;
	t_list	*commands;

	commands = core->line.cmds;
	if (ft_lstsize(commands) == 1)
		errcode = run_single((t_command *)commands->content, core->env);
	//TODO make run_multiple function, it should take all structure and create pipes and all
	// else
	// 	pipex(commands);
	return (EXIT_SUCCESS);
}
