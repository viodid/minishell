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

char	*get_env(char *key, char **envp)
{
	int		i;
	int		keylen;

	if (!envp)
		return (NULL);
	key = ft_strjoin(key, "=");
	keylen = ft_strlen(key);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(key, envp[i], keylen))
			return (free(key), ft_strchr(envp[i], '=') + 1);
	}
	return (free(key), NULL);
}
