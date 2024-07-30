/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:28:59 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/07/16 18:28:59 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**get_env_array(t_data *core)
{
	int		i;
	char	**envp;
	t_list	*tmp;

	i = 0;
	tmp = core->env;
	envp = ft_calloc(ft_lstsize(tmp) + 1, sizeof(char *));
	if (!envp)
		return (NULL);
	while (tmp)
	{
		envp[i] = ft_strjoin(((t_var *)tmp->content)->key, "=");
		if (!envp[i])
			return (ft_dfree((void **)envp), NULL);
		envp[i] = ft_strjoin_f1(envp[i], ((t_var *)tmp->content)->value);
		if (!envp[i])
			return (ft_dfree((void **)envp), NULL);
		tmp = tmp->next;
		i++;
	}
	return (envp);
}
