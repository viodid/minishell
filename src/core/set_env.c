/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:56:20 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/31 19:19:34 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_var	*split_var(char *var_brut)
{
	char	*tmpenv;
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	tmpenv = ft_strdup(var_brut);
	if (!tmpenv)
		return (free(var), NULL);
	var->key = ft_substr(tmpenv, 0, ft_strchr(tmpenv, '=') - tmpenv);
	free(tmpenv);
	if (!var->key)
		return (free(var), NULL);
	tmpenv = ft_strdup(var_brut);
	if (!tmpenv)
		return (free(var), free(var->key), NULL);
	if (!ft_strchr(tmpenv, '='))
	{
		var->value = NULL;
		return (free(tmpenv), var);
	}
	var->value = ft_strdup(ft_strchr(tmpenv, '=') + 1);
	if (!var->value)
		return (free(tmpenv), free(var), free(var->key), NULL);
	return (free(tmpenv), var);
}

t_list	*set_env(char **envp)
{
	int		i;
	t_list	*ret;
	t_var	*var;

	i = -1;
	ret = NULL;
	while (envp[++i])
	{
		var = split_var(envp[i]);
		ft_lstadd_back(&ret, ft_lstnew(var));
	}
	return (ret);
}
