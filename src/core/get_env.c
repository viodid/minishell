/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 18:54:21 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/06/09 18:54:24 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_var	*get_env(t_data *core, char *key)
{
	int		keylen;
	t_list	*tmp;

	tmp = core->envp;
	keylen = ft_strlen(key);
	while (tmp)
	{
		if (!ft_strncmp(key, ((t_var *)(tmp->content))->key, keylen))
			return ((t_var *)(tmp->content));
		tmp = tmp->next;
	}
	return (NULL);
}
