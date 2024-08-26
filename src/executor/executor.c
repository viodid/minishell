/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/26 20:51:11 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	isbuiltin(t_command *cmd)
{
	char	*command;

	if (cmd->tokens && cmd->tokens->content)
		command = ((t_token *)cmd->tokens->content)->value;
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
	return (EXIT_SUCCESS);
}

int	run_single(t_data *core, t_command *command, t_list *env, int *stdinbak)
{
	int	errcode;
	(void)env;

	errcode = redirect_input((t_list *)command->redirs, stdinbak);
	if (errcode == -1)
		return (errcode);
	if (isbuiltin(command))
		exec_builtin(core, command);
	//TODO make execution after redirection

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
		errcode = run_single(core, (t_command *)commands->content, core->env,
				&core->line.stdinbak);
	printf("stdinbak %i\n", core->line.stdinbak);
	//TODO make run_multiple function, it should take all structure and create pipes and all
	// else
	// 	pipex(commands);
	return (errcode);
}
