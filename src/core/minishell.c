/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:07 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/09 21:10:21 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// requiert un refractor
/* int	tmp_exec(char *cmd, t_data *core)
{
	if (!cmd)
		return (EXIT_FAILURE);
	else if (!ft_strncmp(cmd, "cd ", 3))
		ft_cd(core, cmd + 3);
	else if (!ft_strncmp(cmd, "echo", 4))
		ft_echo(!ft_strncmp(cmd, "echo -n", 7), &cmd);
		// ft_echo(!ft_strncmp(cmd, "echo -n", 7), cmd + 4 + (!ft_strncmp(cmd, "echo -n", 7) * 3));
	else if (!ft_strncmp(cmd, "env", 4))
		ft_env(core);
	else if (!ft_strncmp(cmd, "exit", 4))
		ft_exit(core);
	else if (!ft_strncmp(cmd, "export ", 7) && ft_strchr(cmd, '='))
		ft_export(core, cmd + 7);
	else if (!ft_strncmp(cmd, "pwd", 4))
		ft_pwd(core);
	else if (!ft_strncmp(cmd, "unset ", 6))
		ft_unset(core, cmd + 6);
	else
		printf("%s\n", cmd);
	return (EXIT_SUCCESS);
} */

int	minishell(t_data *core)
{
	int			retcode;
	// char		*str;
	// char		**cmds;

	errno = 0;
	parser(core);
	if (errno)
		return(EXIT_SUCCESS);
	// retcode = tmp_exec(str, core);
	retcode = executor(core);
	// ft_dfree((void **)cmds);
	return (retcode);
}
