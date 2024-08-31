/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 17:07:48 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/31 21:08:21 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_single(t_data *core, char *key)
{
	t_list	*tmp;
	t_var	*var;

	tmp = core->env;
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

int	ft_unset(t_data *core, char **args)
{
	int	i;

	i = 0;
	while (args[++i])
		unset_single(core, args[i]);
	return (EXIT_SUCCESS);
}
