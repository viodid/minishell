/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:07:48 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/26 20:20:30 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

// int	ft_unset(t_data *core, char *key)
int	ft_unset(t_list *env, char *key)
{
	t_list	*tmp;
	t_var	*var;

	tmp = env;
	var = get_env(env, key);
	while (tmp && tmp->next)
	{
		if (tmp->next->content == var)
			break;
		tmp = tmp->next;
	}
	ft_lstdelnext(&tmp, &free_var);
	return (EXIT_SUCCESS);
}
