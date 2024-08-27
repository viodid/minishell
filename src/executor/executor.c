/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/27 21:50:28 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	run_single(t_data *core, t_command *command)
{
	int	errcode;

	errcode = redirect_input((t_list *)command->redirs, &core->line.stdinbak);
	if (errcode == -1)
		return (perror("post redirect"), errcode);
	if (command->tokens && isbuiltin(command))
		exec_builtin(core, command);
	//TODO make execution after redirection
	dup2(core->line.stdinbak, STDIN_FILENO);
	unlink(HDOC_TMP);
	return (errcode);
}

int	executor(t_data *core)
{
	int		errcode;
	t_list	*commands;

	errcode = EXIT_SUCCESS;
	commands = core->line.cmds;
	if (ft_lstsize(commands) == 1)
		errcode = run_single(core, (t_command *)commands->content);
	//TODO make run_multiple function, it should take all structure and create pipes and all
	// else
	// 	pipex(commands);
	return (errcode);
}
