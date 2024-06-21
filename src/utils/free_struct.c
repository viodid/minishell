/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 17:12:21 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/06/21 17:12:21 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_var(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	free(var->key);
	free(var->value);
}

void	free_struct(t_data *core)
{
	ft_lstclear(&core->envl, &free_var);
}

