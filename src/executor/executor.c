/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/16 20:27:58 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_selector(t_data *core, t_command *command, int cmd_nb)
{
	int		retcode;
	char	*cmdpath;
	char	**args;
	char	**envp;

	args = get_arg_array(command);
	if (!args)
		return (EXIT_FAILURE);
	envp = get_env_array(core);
	if (!envp)
		return (free(args), EXIT_FAILURE);
	cmdpath = args[0];
	if (isbuiltin(args[0]))
	{
		retcode = exec_builtin(core, cmdpath, args, core->line->nbcommands > 1);
		if (core->line->nbcommands == 1)
			return (ft_dfree((void **)envp), free(args), retcode);
	}
	else
	{
		cmdpath = get_cmdpath(core, args[0], get_env(core, "PATH"));
		if (!cmdpath)
		{
			free_struct(core);
			free_line(core->line);
			ft_dfree((void **)envp);
			free(args);
			exit(EXIT_FAILURE);
		}
	}
	if (execve(cmdpath, args, envp))
		perror(args[0]);
	free(cmdpath);
	free_struct(core);
	free_line(core->line);
	ft_dfree((void **)envp);
	free(args);
	exit(retcode);
}

int	run_single(t_data *core, t_command *command, t_fds fds, int cmd_nb)
{
	int		retcode;

	retcode = EXIT_SUCCESS;
	do_piperedir(core, command, fds, cmd_nb);
	do_fileredir(command, fds);
	if (command->tokens)
		retcode = exec_selector(core, command, cmd_nb);
	return (retcode);
}

int	process_single(t_data *core, t_command *command, int cmd_nb)
{
	int		pid;

	set_fds(&command->fds, core, cmd_nb);
	get_redirs(command, &command->fds);
	pid = core->line->pids[cmd_nb];
	if (command->tokens && (core->line->nbcommands > 1
			|| !isbuiltin(((t_token *)command->tokens->content)->value)))
	{
		pid = fork(); //!start of child process
		if (pid == 0)
			run_single(core, command, command->fds, cmd_nb);
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

int	process_multiple(t_data *core, t_list *commands)
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
	while (1)
		if (waitpid(-1, NULL, 0) < 0) //TODO handle Process &status, external func
			break ;
	return (EXIT_SUCCESS);
}

int	executor(t_data *core)
{
	t_list	*commands;

	commands = core->line->cmds;
	if (do_heredocs(commands) || init_pipes(core) || save_stdfds(core))
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
