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

char	*get_tmpname(void)
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
		ret = ft_strjoin_f2("tmp/minishell-", id);
		if (!ret)
			return (NULL);
		if (access(ret, F_OK) == -1)
			return (ret);
		free(ret);
		i++;
	}
	return (NULL);
}

char	*heredoc_loop(char *limiter, char *tmpname)
{
	int		fd;
	char	*line;

	if (!tmpname)
	{
		tmpname = get_tmpname();
		if (!tmpname)
			return (NULL);
	}
	else
		unlink(tmpname);
	fd = open(tmpname, O_RDWR | O_CREAT | O_EXCL, 0644);
	if (fd == -1 || access(tmpname, F_OK) == -1)
		return (NULL);
	line = readline(">");
	while (ft_strncmp(line, limiter, ft_strlen(limiter) + 1))
	{
		ft_putendl_fd(line, fd);
		free(line);
		line = readline(">");
	}
	free(line);
	close(fd);
	return (tmpname);
}

char	*do_heredoc(t_list *redirs, t_redir **lasthdoc)
{
	char	*ret;
	t_redir	*redir;

	ret = NULL;
	while (redirs && redirs->content)
	{
		redir = (t_redir *)redirs->content;
		if (redir->type == HEREDOC)
		{
			ret = heredoc_loop(redir->file, ret);
			if (!ret)
				return (perror("heredoc"), NULL);
			*lasthdoc = redir;
		}
		redirs = redirs->next;
	}
	return (ret);
}

int	do_heredocs(t_list *commands)
{
	t_command	*command;
	t_list		*redirs;
	t_redir		*lasthdoc;
	char		*tmpfile;

	while (commands && commands->content)
	{
		tmpfile = NULL;
		command = (t_command *)commands->content;
		redirs = command->redirs;
		tmpfile = do_heredoc(redirs, &lasthdoc);
		if (tmpfile)
		{
			free(lasthdoc->file);
			lasthdoc->file = tmpfile;
			lasthdoc->type = H_INPUT;
		}
		commands = commands->next;
	}
	return (EXIT_SUCCESS);
}
