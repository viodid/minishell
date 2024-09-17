/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 20:23:59 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/17 20:24:02 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_tmpname()
{
	int		i;
	char	*id;
	char	*ret;

	i = 0;
	while (i < INT32_MAX)
	{
		id = ft_itoa(i);
		if (!id)
			return (NULL);
		ret = ft_strjoin_f2("minishell-", id);
		if (!ret)
			return (NULL);
		if (access(ret, F_OK) == -1)
			return (ret);
		free(ret);
		i++;
	}
	return (NULL);
}

int	heredoc_loop(char *limiter, int fd, int iscommand)
{
	char	*line;
	char	*tmpname;

	close(fd);
	// if (!access(HDOC_TMP, R_OK))
	// 	unlink(HDOC_TMP);
	tmpname = get_tmpname();
	if (!tmpname)
		return (-1);
	fd = open(tmpname, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd == -1 || access(tmpname, F_OK) == -1)
		return (fd);
	line = readline(">");
	while (ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline(">");
	}
	if (!iscommand)
	{
		fd = 0;
		unlink(tmpname);
	}
	return (fd);
}
