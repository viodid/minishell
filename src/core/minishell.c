/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:07 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/26 20:21:59 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tmp_exec(char *cmd, t_data *core)
{
	if (!cmd)
		return (EXIT_FAILURE);
	else if (!ft_strncmp(cmd, "cd ", 3))
		ft_cd(core->env, cmd + 3);
	else if (!ft_strncmp(cmd, "echo", 4))
		ft_echo(!ft_strncmp(cmd, "echo -n", 7), &cmd);
		// ft_echo(!ft_strncmp(cmd, "echo -n", 7), cmd + 4 + (!ft_strncmp(cmd, "echo -n", 7) * 3));
	else if (!ft_strncmp(cmd, "env", 4))
		ft_env(core->env);
	else if (!ft_strncmp(cmd, "exit", 4))
		ft_exit(core);
	else if (!ft_strncmp(cmd, "export ", 7) && ft_strchr(cmd, '='))
		ft_export(core->env, cmd + 7);
	else if (!ft_strncmp(cmd, "pwd", 4))
		ft_pwd(core->env);
	else if (!ft_strncmp(cmd, "unset ", 6))
		ft_unset(core->env, cmd + 6);
	else
		printf("%s\n", cmd);
	return (EXIT_SUCCESS);
}

int	minishell(t_data *core)
{
	int			retcode;
	char		*str;
	char		**cmds;

	str = readline("minishell >");
	cmds = ft_split(str, '|');
	if (!cmds)
		return (EXIT_SUCCESS);
	if (core->line.cmds)
		ft_lstclear(&core->line.cmds, free_cmd);
	temp_parser(core, cmds);

	// retcode = tmp_exec(str, core);
	retcode = executor(core);
	add_history(str);
	free(str);
	ft_dfree((void **)cmds);
	return (retcode);
}
