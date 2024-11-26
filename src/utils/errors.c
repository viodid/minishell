/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 21:05:53 by dyunta            #+#    #+#             */
/*   Updated: 2024/11/24 11:26:45 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int32_t	send_error(char *err_msg, char *detail_msg, int exit_status)
{
	ft_putstr_fd("ˢʰᵉˡˡ: ", STDERR_FILENO);
	ft_putstr_fd(err_msg, STDERR_FILENO);
	ft_putendl_fd(detail_msg, STDERR_FILENO);
	return (exit_status);
}
