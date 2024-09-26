/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:07 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/10 20:17:17 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	minishell(t_data *core)
{
	int			retcode;
	char		**cmds;

	errno = 0;
	parser(core);
	if (errno)
		return(EXIT_SUCCESS);
	retcode = executor(core);
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
