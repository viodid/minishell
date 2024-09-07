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

int	run_single(t_data *core, t_command *command, t_fds fds)
{
	int		retcode;

	retcode = EXIT_SUCCESS;
	if (hasinput(command->redirs))
	{
		fds.fdin = redirect_input((t_list *)command->redirs, fds,
				&core->line.stdinbak, (command->tokens && 1));
		if (fds.fdin == -1)
			return (perror("post redirect"), -1);
	}
	// if (hasoutput(command->redirs))
	// {
	// 	fds.fdout = redirect_output((t_list *)command->redirs, fds,
	// 			&core->line.stdoutbak, (command->tokens && 1));
	// 	if (fds.fdout == -1)
	// 		return (perror("post redirect"), -1);
	// }
	if (command->tokens)
		retcode = exec_selector(core, command);
	if (hasinput(command->redirs) && fds.stdfdin == STDIN_FILENO)
		dup2(core->line.stdinbak, fds.stdfdin);
	if (hasoutput(command->redirs) && fds.stdfdout == STDOUT_FILENO)
		dup2(core->line.stdoutbak, fds.stdfdin);
	unlink(HDOC_TMP);
	return (retcode);
}

int	process_single(t_data *core, t_command *command, int npid)
{
	t_fds	fds;
	int		pid;
	int		retcode;

	pid = core->line.pids[npid];
	if (set_fds(&fds, core, npid))
		return (errno);
	if (command->tokens && (core->line.nbcommands > 1
			|| !isbuiltin(((t_token *)command->tokens->content)->value)))
	{
		printf("forking\n");
		pid = fork(); //!start of child process
		if (pid == 0) // child case
			retcode = run_single(core, command, fds);
		else
			return (EXIT_SUCCESS);
	}
	else
		retcode = run_single(core, command, fds);
	return (retcode);
}

int	executor(t_data *core)
{
	int		i;
	int		retcode;
	t_list	*commands;

	i = 0;
	retcode = EXIT_SUCCESS;
	commands = core->line.cmds;
	if (ft_lstsize(commands) == 1)
		retcode = process_single(core, (t_command *)commands->content, 0);
	else
	{	//TODO go handle pipes, start allocating pipes
		while (commands)
		{
			retcode = process_single(core, (t_command *)commands->content, i);
			if (retcode)
				return (retcode);
			commands = commands->next;
			i++;
			while (1)
				if (waitpid(-1, NULL, 0) < 0)
					break ;
		}
	}
	return (retcode);
}
