/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:21:10 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/06/19 15:21:10 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//TODO BUG: export seems to be erasing all previous env vars
int	export(t_data *core, char *var)
{
	t_var	*envvar;
	t_var	*tmp;

	tmp = split_var(var);
	envvar = get_env(core, tmp->key);
	if (envvar)
	{
		free(envvar->value);
		envvar->value = ft_strdup(tmp->value);
		free_var(tmp);
	}
	else
		ft_lstadd_back(&core->envp, ft_lstnew(tmp));
	return (EXIT_SUCCESS);	
}
