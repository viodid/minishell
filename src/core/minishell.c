/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:07 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/10/24 19:52:12 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	extra_parsings(t_data *core)
{
	int	i;

	i = 0;
	if (core->line)
	{
		core->line->nbcommands = 0;
		if (core->line->cmds)
			core->line->nbcommands = ft_lstsize(core->line->cmds);
		if (core->line->nbcommands > 1)
		{
			core->line->fds = ft_calloc(core->line->nbcommands, sizeof(int *));
			while (i < core->line->nbcommands)
				core->line->fds[i++] = ft_calloc(2, sizeof(int));
		}
	}
}

int	check_retstatus(int status)
{
	if (WIFEXITED(status) == TRUE)
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status) == TRUE)
		return (WTERMSIG(status));
	return (EXIT_SUCCESS);
}

int	minishell(t_data *core)
{
	int		i;
	int		wstatus;
	int		retcode;

	errno = 0;
	i = 0;
	parser(core);
	extra_parsings(core);
	if (errno)
		return (EXIT_SUCCESS);
	retcode = executor(core);
	while (core->line->haschild)
	{
		i = waitpid(-1, &wstatus, 0);
		if (i < 0)
		{
			core->errcode = check_retstatus(wstatus);
			break ;
		}
	}
	return (retcode);
}

// int	minishell(t_data *core)
// {
// 	int			retcode;
// 	char		*str;
// 	char		**cmds;

// 	str = readline("ˢʰᵉˡˡ$>");
// 	cmds = ft_split(str, '|');
// 	if (!cmds)
// 		return (EXIT_SUCCESS);
// 	if (core->line && core->line->cmds)
// 		ft_lstclear(&core->line->cmds, free_cmd);
// 	tmp_parser(core, cmds);

// 	retcode = executor(core);
// 	if (ft_strlen(str))
// 		add_history(str);
// 	free(str);
// 	ft_dfree((void **)cmds);
// 	return (retcode);
// }
