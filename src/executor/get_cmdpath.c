/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 17:53:44 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/03 17:59:56 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_cmdpath(t_data *core, char *cmd, t_var *envpaths)
{
	int		i;
	char	*ret;
	char	**paths;
	(void)core;

	if (!access(cmd, X_OK))
		return (cmd);
	i = -1;
	paths = ft_split(envpaths->value, ':');
	if (!paths)
		return (perror("paths"), NULL); //TODO decide best way to handle error
	while (paths[++i])
	{
		ret = ft_strjoin(paths[i], "/");
		if (!ret)
			return (perror("paths"), ft_dfree((void **)paths), NULL); //TODO decide best way to handle error
		ret = ft_strjoin_f1(ret, cmd);
		if (!ret)
			return (perror("paths"), ft_dfree((void **)paths), NULL); //TODO decide best way to handle error
		if (!access(ret, X_OK))
			return (ft_dfree((void **)paths), ret);
	}
	return (ft_dfree((void **)paths), free(ret), NULL);
}
