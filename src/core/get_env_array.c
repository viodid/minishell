/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:28:59 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/30 23:50:38 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_env_array(t_list *env)
{
	int		i;
	char	**envp;

	i = 0;
	envp = ft_calloc(ft_lstsize(env) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	while (env)
	{
		if (((t_var *)env->content)->value)
		{
			envp[i] = ft_strjoin(((t_var *)env->content)->key, "=");
			if (!envp[i])
				return (ft_dfree((void **)envp), NULL);
			envp[i] = ft_strjoin_f1(envp[i], ((t_var *)env->content)->value);
			if (!envp[i])
				return (ft_dfree((void **)envp), NULL);
		}
		else
			envp[i] = ((t_var *)env->content)->key;
		env = env->next;
		i++;
	}
	return (envp);
}
