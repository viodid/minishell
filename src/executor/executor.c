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
	cmdpath = get_cmdpath(core, args[0], get_env(core, "PATH"));
	if (isbuiltin(args[0]))
	{
		free(cmdpath);
		retcode = exec_builtin(core, args[0], args);
	}
	else
	{
		retcode = execve(cmdpath, args, envp);
		free(cmdpath);
		//TODO print error here?
	}
	return (ft_dfree((void **)envp), free(args), retcode);
}

int	run_single(t_data *core, t_command *command)
{
	int	fdin;
	int	retcode;

	retcode = EXIT_SUCCESS;
	if (hasinput(command->redirs))
	{
		fdin = redirect_input((t_list *)command->redirs, &core->line.stdinbak,
				(command->tokens && 1));
		if (fdin == -1)
			return (perror("post redirect"), -1);
	}
	if (command->tokens)
		retcode = exec_selector(core, command);
	if (hasinput(command->redirs))
	{
		dup2(core->line.stdinbak, STDIN_FILENO);
		unlink(HDOC_TMP);
	}
	return (retcode);
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
