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

int	run_single(t_data *core, t_command *command, t_fds fds, int cmd_nb)
{
	int		retcode;

	retcode = EXIT_SUCCESS;
	do_piperedir(core, fds, cmd_nb);
	do_fileredir(fds);
	// dprintf(2, ">%i\n", getpid());
	// print_fds(fds);
	if (command->tokens)
		retcode = exec_selector(core, command);
	return (retcode);
}

int	process_single(t_data *core, t_command *command, t_fds fds, int cmd_nb)
{
	int		pid;
	int		retcode;

	set_fds(&fds, core, cmd_nb);
	redirect_files(command, &fds);
	pid = core->line->pids[cmd_nb];
	// print_fds(fds);
	if (command->tokens && (core->line->nbcommands > 1
			|| !isbuiltin(((t_token *)command->tokens->content)->value)))
	{
		printf("forking\n");
		pid = fork(); //!start of child process
		if (pid == 0) // child case
			retcode = run_single(core, command, fds, cmd_nb);
		else
		{
			close_parent_pipes(core, cmd_nb);
			return (EXIT_SUCCESS);
		}
	}
	else
	{
		retcode = run_single(core, command, fds, cmd_nb);
		reset_stdfds(core);
	}
	return (retcode);
}

int	process_multiple(t_data *core, t_list *commands, t_fds *fds)
{
	int			i;
	t_command	*command;

	i = 0;
	while (commands)
	{
		command = (t_command *)commands->content;
		process_single(core, command, fds[i], i);
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
	t_fds	*fds;
	t_list	*commands;

	fds = malloc(core->line->nbcommands * sizeof(t_fds));
	ft_memset((void *)fds, -1, core->line->nbcommands * sizeof(t_fds));
	commands = core->line->cmds;
	if (do_heredocs(commands) || init_pipes(core) || save_stdfds(core))
		return (EXIT_FAILURE);
	commands = core->line->cmds;
	if (ft_lstsize(commands) == 0)
		return (EXIT_SUCCESS);
	else if (ft_lstsize(commands) > 1)
		return (process_multiple(core, commands, fds));
	retcode = process_single(core, (t_command *)commands->content, fds[0], 0);
	if (!core->line->pids[0] && reset_stdfds(core))
	{
		free_struct(core);
		exit(EXIT_FAILURE);
	}
	return (retcode);
}
