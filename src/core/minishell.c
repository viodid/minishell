/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:07 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/03/22 18:27:10 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	tmp_exec(char *cmd, t_data *core)
{
	if (!cmd)
		return (EXIT_FAILURE);
	else if (!ft_strncmp(cmd, "cd ", 3))
		cd(core, cmd + 3);
	else if (!ft_strncmp(cmd, "echo", 4))
		echo(!ft_strncmp(cmd, "echo -n", 7), cmd + 4 + (!ft_strncmp(cmd, "echo -n", 7) * 3));
	else if (!ft_strncmp(cmd, "env", 4))
		env(core);
	else if (!ft_strncmp(cmd, "exit", 4))
		builtin_exit(core);
	else if (!ft_strncmp(cmd, "export ", 7) && ft_strchr(cmd, '='))
		export(core, cmd + 7);
	else if (!ft_strncmp(cmd, "pwd", 4))
		pwd(core);
	else if (!ft_strncmp(cmd, "unset ", 6))
		unset(core, cmd + 6);
	else
		printf("%s\n", cmd);
	return (EXIT_SUCCESS);
}

int	minishell(t_data *core)
{
	int		retcode;
	char	*str;

	str = readline("minishell >");
	retcode = tmp_exec(str, core);
	add_history(str);
	free(str);

	return (retcode);
}
