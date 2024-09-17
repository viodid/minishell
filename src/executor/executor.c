/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:18:39 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/09 21:30:56 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	exec_selector(t_data *core, t_command *command)
{
	int		retcode;
	char	*cmdpath;
	char	**args;
	char	**envp;

	args = get_arg_array(command);
	envp = get_env_array(core);
	cmdpath = args[0];
	if (!isbuiltin(args[0]))
		cmdpath = get_cmdpath(core, args[0], get_env(core, "PATH"));
	if (isbuiltin(args[0]))
	{
		retcode = exec_builtin(core, cmdpath, args, core->line->nbcommands > 1);
		if (core->line->nbcommands == 1)
			return (ft_dfree((void **)envp), free(args), retcode);
	}
	else
	{
		if (execve(cmdpath, args, envp))
			perror(args[0]);
		free(cmdpath);
	}
	ft_dfree((void **)envp);
	free(args);
	exit(retcode);
}

int	run_single(t_data *core, t_command *command, t_fds fds)
{
	int		retcode;

	retcode = EXIT_SUCCESS;
	redirect_files(command, &fds);
	if (command->tokens)
		retcode = exec_selector(core, command);
	unlink(HDOC_TMP);
	return (retcode);
}

int	process_single(t_data *core, t_command *command, int cmd_nb)
{
	t_fds	fds;
	int		pid;
	int		retcode;

	pid = core->line->pids[cmd_nb];
	if (set_fds(&fds, core, cmd_nb))
		return (errno);
	if (command->tokens && (core->line->nbcommands > 1
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
	// fprintf(stderr, "unlinking %i\n", unlink(HDOC_TMP));
	return (retcode);
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
	int		retcode;
	t_list	*commands;

	commands = core->line->cmds;
	if (save_stdfds(core) || init_pipes(core))
		return (EXIT_FAILURE);
	if (ft_lstsize(commands) == 0)
		return (EXIT_SUCCESS);
	else if (ft_lstsize(commands) > 1)
		return (process_multiple(core, commands));
	retcode = process_single(core, (t_command *)commands->content, 0);
	if (!core->line->pids[0] && reset_stdfds(core))
	{
		free_struct(core);
		exit(EXIT_FAILURE);
	}
	return (retcode);
}
