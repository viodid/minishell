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

int	minishell(t_data *core)
{
	int			retcode;
	char		**cmds;
	(void)cmds;

	errno = 0;
	parser(core);
	extra_parsings(core);
	if (errno)
		return (EXIT_SUCCESS);
	retcode = executor(core);
	// ft_fdprintf(2, "size: %i\n", ft_lstsize(core->env));
	retcode = 0;
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
