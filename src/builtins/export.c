/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:21:10 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/31 20:54:11 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_valid(char *var)	//TODO figure out which chars are ok '_', '-', '.', ...
{
	int	i;

	i = 0;
	if (!ft_isalpha(var[0]))
		return (FALSE);
	while (var[++i])
		if (!ft_isalnum(var[i]))
			return (FALSE);
	return (TRUE);
}

int	export_single(t_data *core, char *arg)
{
	t_var	*envvar;
	t_var	*tmp;

	tmp = split_var(arg);
	if (!is_valid(tmp->key))
		return (free_var(tmp), EXIT_FAILURE);
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
	int	i;
	int	retcode;

	if (!args[1])
	{
		ft_lstiter(core->env, print_var_exp);
		return (EXIT_SUCCESS);
	}
	retcode = EXIT_SUCCESS;
	i = 0;
	while (args[++i])
	{
		retcode = export_single(core, args[i]);
		if (retcode)
		{
			core->errcode = EXIT_FAILURE;
			printf("export: `%s': not a valid identifier\n", args[i]);
		}
	}
	return (retcode);
}
