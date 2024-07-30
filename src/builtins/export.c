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

//TODO take multiple arguments and export all all the valid ones
// int	ft_export(t_list **env, char **args)
int	ft_export(t_data *core, char *var)
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
		ft_lstadd_back(&core->env, ft_lstnew(tmp));
	return (EXIT_SUCCESS);
}
