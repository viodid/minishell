/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/03 17:54:05 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_arg_array(t_command *command)
{
	int		i;
	char	**ret;
	t_list	*tmp;
	t_token	*token;

	i = 0;
	ret = ft_calloc(ft_lstsize(command->tokens) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	tmp = command->tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		ret[i++] = token->value;
		tmp = tmp->next;
	}
	return (ret);
}

int	exec_selector(t_data *core, t_command *command)
{
	int		retcode;
	char	*cmdpath;
	char	**args;
	char	**envp;

	args = get_arg_array(command);
	envp = get_env_array(core);
	// cmdpath = get_cmdpath(core, args[0]);
	cmdpath = args[0];
	if (isbuiltin(command, cmdpath))
	{
		retcode = exec_builtin(core, cmdpath, args);
	}
	else
	{
		retcode = execve(cmdpath, args, envp);
		//TODO print error here?
	}
	return (ft_dfree((void **)envp), free(args), retcode);
}

int	run_single(t_data *core, t_command *command)
{
	int	fdin;

	fdin = redirect_input((t_list *)command->redirs, &core->line.stdinbak);
	if (fdin == -1)
		return (perror("post redirect"), fdin);
	if (command->tokens)
		exec_selector(core, command);
	dup2(core->line.stdinbak, STDIN_FILENO);
	unlink(HDOC_TMP);
	return (fdin);
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
