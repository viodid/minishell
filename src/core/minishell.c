/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:27:07 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/27 00:02:15 by dyunta           ###   ########.fr       */
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

