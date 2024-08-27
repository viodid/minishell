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
