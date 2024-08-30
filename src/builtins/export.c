/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:21:10 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/30 23:54:47 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
//TODO handle "export test =var" use case, =var is an invalid var name

int	export_single(t_data *core, char *arg)
{
	t_var	*envvar;
	t_var	*tmp;

	tmp = split_var(arg);
	envvar = get_env(core, tmp->key);
	if (envvar)
	{
		if (tmp->value)
		{
			free(envvar->value);
			envvar->value = ft_strdup(tmp->value);
		}
		free_var(tmp);
	}
	else
		ft_lstadd_back(&core->env, ft_lstnew(tmp));
	return (EXIT_SUCCESS);
}

int	ft_export(t_data *core, char **args)
{
	int		i;

	if (!args[1])
		ft_lstiter(core->env, print_var_exp);
	i = 0;
	while (args[++i])
		export_single(core, args[i]);
	return (EXIT_SUCCESS);
}
