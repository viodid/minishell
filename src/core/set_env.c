/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:56:20 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/06/21 16:56:20 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_list	*set_env(char **envp)
{
	int		i;
	char	*tmpenv;
	t_var	*var;
	t_list	*ret;

	i = -1;
	ret = NULL;
	while (envp[++i])
	{
		var = ft_calloc(1, sizeof(t_var));
		tmpenv = ft_strdup(envp[i]);
		var->key = ft_substr(tmpenv, 0, ft_strchr(tmpenv, '=') - tmpenv);
		free(tmpenv);
		tmpenv = ft_strdup(envp[i]);
		var->value = ft_strdup(ft_strchr(tmpenv, '=') + 1);
		free(tmpenv);
		ft_lstadd_back(&ret, ft_lstnew(var));
	}
	return (ret);
}
