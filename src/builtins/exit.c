/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 21:02:59 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/06/24 21:02:59 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	ft_exit(t_data *core, int status)
int	ft_exit(t_data *core)
{
	free_struct(core);
	exit(EXIT_SUCCESS);
}
