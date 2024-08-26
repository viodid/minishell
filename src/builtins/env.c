/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:57:58 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/26 20:14:16 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	ft_env(t_list *env)
int	ft_env(t_list *env)
{
	ft_lstiter(env, &print_var);
	return(EXIT_SUCCESS);
}
