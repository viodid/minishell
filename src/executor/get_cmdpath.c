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

char	**get_arg_array(t_command *command)
{
	int		i;
	char	**ret;
	t_list	*tmp;
	t_token	*token;

	i = 0;
	ret = ft_calloc(ft_lstsize(command->tokens) + 1, sizeof(char *));
	if (!ret)
		return (NULL);
	tmp = command->tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		ret[i++] = token->value;
		tmp = tmp->next;
	}
	return (ret);
}

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
		return (perror("path allocation"), NULL);
	while (paths[++i])
	{
		ret = ft_strjoin(paths[i], "/");
		if (!ret)
			return (perror("path allocation"), ft_dfree((void **)paths), NULL);
		ret = ft_strjoin_f1(ret, cmd);
		if (!ret)
			return (perror("path allocation"), ft_dfree((void **)paths), NULL);
		if (!access(ret, X_OK))
			return (ft_dfree((void **)paths), ret);
	}
	return (dprintf(2, "%s: command not found\n", cmd),
		ft_dfree((void **)paths), free(ret), NULL);
}
