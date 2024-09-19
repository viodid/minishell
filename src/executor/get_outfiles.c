/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_outfiles.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:31:31 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/09 19:55:43 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	hasoutput(t_list *redirs)
{
	t_redir	*redir;
	t_list	*tmp;

	if (!redirs || !redirs->content)
		return (FALSE);
	tmp = redirs;
	while (tmp)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == APPEND || redir->type == OUTPUT)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

int	create_outfile(char *filename, int fd, int type)
{
	int	flags;

	if (fd > 2)
		close(fd);
	if (type == OUTPUT)
		flags = O_RDWR | O_CREAT | O_TRUNC;
	else
		flags = O_RDWR | O_CREAT | O_APPEND;
	fd = open(filename, flags, 0644);
	return (fd);
}

int	get_output(t_list *redirs)
{
	int		fd;
	t_redir	*redir;
	t_list	*tmp;

	tmp = redirs;
	fd = 1;
	while (tmp && fd != -1)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == OUTPUT || redir->type == APPEND)
			fd = create_outfile(redir->file, fd, redir->type);
		tmp = tmp->next;
	}
	return (fd);
}

int	get_outfiles(t_list *redirs, t_fds *fds)
{
	fds->fdout = get_output(redirs);
	if (fds->fdout == -1 || !fds->fdout)
		return (fds->fdout);
	return (fds->fdout);
}
