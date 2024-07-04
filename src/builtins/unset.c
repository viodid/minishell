/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:07:48 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/06/22 17:07:48 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset(t_data *core, char *key)
{
	t_list	*tmp;
	t_var	*var;

	tmp = core->envp;
	var = get_env(core, key);
	while (tmp && tmp->next)
	{
		if (tmp->next->content == var)
			break;
		tmp = tmp->next;
	}
	ft_lstdelnext(&tmp, &free_var);
	return (EXIT_SUCCESS);
}
