/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/11/28 19:48:51 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	exec_selector(t_data *core, t_command *command)
{
	int		retcode;
	char	*cmdpath;
	char	**args;
	char	**envp;

	args = get_arg_array(command);
	if (!args)
		exit(EXIT_FAILURE);
	envp = get_env_array(core->env);
	if (!envp)
		exit(EXIT_FAILURE);
	if (isbuiltin(args[0]))
	{
		retcode = exec_builtin(core, args[0], args);
		return (ft_dfree((void **)envp), free(args), retcode);
	}
	cmdpath = get_cmdpath(args[0], get_env(core, "PATH"));
	if (!cmdpath)
		return (ft_dfree((void **)envp), free(args), EXIT_FAILURE);
	if (execve(cmdpath, args, envp))
		perror(args[0]);
	exit(EXIT_FAILURE);
}

static int	run_single(t_data *core, t_command *command, t_fds fds, int cmd_nb)
{
	int		retcode;

	retcode = EXIT_SUCCESS;
	do_piperedir(core, cmd_nb);
	if (do_fileredir(command, fds))
	{
		core->errcode = EXIT_FAILURE;
		return (EXIT_FAILURE);
	}
	if (command->tokens)
	{
		retcode = exec_selector(core, command);
		core->errcode = retcode;
	}
	return (retcode);
}

static int	process_single(t_data *core, t_command *command, int cmd_nb)
{
	int		pid;

	set_fds(&command->fds, core, cmd_nb);
	get_redirs(command, &command->fds);
	pid = core->line->pids[cmd_nb];
	if (command->tokens && (core->line->nbcommands > 1
			|| !isbuiltin(((t_token *)command->tokens->content)->value)))
	{
		core->line->haschild = 1;
		pid = fork();
		if (pid == 0)
			exit(run_single(core, command, command->fds, cmd_nb));
		else
		{
			close_parent_pipes(core, cmd_nb);
			return (EXIT_SUCCESS);
		}
	}
	else
	{
		run_single(core, command, command->fds, cmd_nb);
		reset_stdfds(core);
	}
	return (EXIT_SUCCESS);
}

static int	process_multiple(t_data *core, t_list *commands)
{
	int			i;
	t_command	*command;

	i = 0;
	while (commands)
	{
		command = (t_command *)commands->content;
		process_single(core, command, i);
		commands = commands->next;
		i++;
	}
	return (EXIT_SUCCESS);
}

int	executor(t_data *core)
{
	t_list	*commands;

	signal_handler(NONIN);
	if (!core->line || !core->line->cmds)
		return (EXIT_SUCCESS);
	if (do_heredocs(core) || init_pipes(core) || save_stdfds(core))
		return (EXIT_FAILURE);
	commands = core->line->cmds;
	if (ft_lstsize(commands) == 0)
		return (EXIT_SUCCESS);
	else if (ft_lstsize(commands) > 1)
		return (process_multiple(core, commands));
	process_single(core, (t_command *)commands->content, 0);
	if (!core->line->pids[0] && reset_stdfds(core))
	{
		free_struct(core);
		free_line(core->line);
		exit(EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
