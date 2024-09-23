/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_infiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 03:08:16 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/09 19:55:43 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	hasinput(t_list *redirs)
{
	t_redir	*redir;
	t_list	*tmp;

	if (!redirs || !redirs->content)
		return (FALSE);
	tmp = redirs;
	while (tmp)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == INPUT || redir->type == H_INPUT)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

int	check_infile(char *infile, int fd, int iscommand)
{
	if (fd > 2)
		close(fd);
	if (iscommand)
		fd = open(infile, O_RDONLY);
	else
		fd = access(infile, R_OK);
	if (fd == -1)
		perror(infile);
	return (fd);
}

int	get_input(t_list *redirs, int iscommand)
{
	int		fd;
	t_redir	*redir;
	t_list	*tmp;

	fd = 0;
	tmp = redirs;
	while (tmp && fd != -1)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == INPUT || redir->type == H_INPUT)
			fd = check_infile(redir->file, fd, iscommand);
		tmp = tmp->next;
	}
	return (fd);
}

int	get_infiles(t_list *redirs, t_fds *fds, int iscommand)
{
	fds->fdin = get_input(redirs, iscommand);
	if (fds->fdin == -1 || !fds->fdin)
		return (fds->fdin);
	return (fds->fdin);
}
