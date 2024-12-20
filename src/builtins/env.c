/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 20:57:58 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/31 23:56:37 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_env(t_data *core)
{
	t_list	*tmp;

	tmp = core->env;
	ft_lstiter(tmp, &print_var_env);
	return (EXIT_SUCCESS);
}
