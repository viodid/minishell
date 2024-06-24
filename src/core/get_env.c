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

t_var	*get_env(char *key, t_data *core)
{
	int	keylen;

	keylen = ft_strlen(key);
	while (core->envp)
	{
		if (!ft_strncmp(key, ((t_var *)(core->envp->content))->key, keylen))
			return ((t_var *)(core->envp->content));
		core->envp = core->envp->next;
	}
	return (NULL);
}
