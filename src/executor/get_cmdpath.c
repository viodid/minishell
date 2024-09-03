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

/* char	*get_envpath(t_data *core, char *cmd, char **envp)
{
	t_count	c;
	char	*ret;
	char	*tmp;
	char	**paths;

	ft_bzero((void *)&c, sizeof(t_count));
	while (envp[c.i] && ft_strncmp(envp[c.i], "PATH", 4))
		c.i++;
	paths = ft_split(ft_strnstr(envp[c.i], "=", 7) + 1, ':');
	if (!paths)
		perror_exit(core, "env variables", 128); //error handling
	while (paths[c.j] && paths[c.j + 1] && access(ret, F_OK))
	{
		if (c.j)
			free(ret);
		c.j++;
		tmp = ft_strjoin(paths[c.j], "/");
		ret = ft_strjoin_f1(tmp, cmd);
	}
	if (!paths[c.j])
		perror_exit(core, paths[c.j], 127); //error handling
	return (ft_dfree((void **)paths), ret);
}

static char	*get_path(t_data *core, char *cmd, char **envp)
{
	if (!cmd)
		return (NULL);
	else if (!*envp)
	{
		if (access(cmd, F_OK) == -1)
			perror_exit(core, cmd, 127); //error handling
		return (ft_strdup(cmd));
	}
	else
		return (get_envpath(core, cmd, envp));
} */

char	*get_cmdpath(t_data *core, char *cmd, t_var *envpaths)
{
	int		i;
	char	*ret;
	char	**paths;

	if (!access(cmd, X_OK))
		return (cmd);
	i = -1;
	paths = ft_split(envpaths->value, ':');
	while (paths[++i])
	{
		ret = ft_strjoin(paths[i], "/");
		ret = ft_strjoin_f1(ret, cmd);
		if (!access(ret, X_OK))
			return (ret);
	}
	return (NULL);
}
