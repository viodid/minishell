/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_infile.c                                  :+:      :+:    :+:   */
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
		if (redir->type == HEREDOC || redir->type == INPUT)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

int	heredoc_loop(char *limiter, int fd, int iscommand)
{
	char	*line;

	close(fd);
	if (!access(HDOC_TMP, R_OK))
		unlink(HDOC_TMP);
	fd = open(HDOC_TMP, O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
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
		unlink(HDOC_TMP);
	}
	return (fd);
}

int	check_infile(char *infile, int fd, int iscommand)
{
	close(fd);
	if (!access(HDOC_TMP, R_OK))
		unlink(HDOC_TMP);
	if (iscommand)
		fd = open(infile, O_RDONLY);
	else
		fd = access(infile, R_OK);
	if (fd == -1)
		perror(infile);
	return (fd);
}

int	get_input(t_list *redirs, int iscommand, int *ishdoc)
{
	int		fd;
	t_redir	*redir;
	t_list	*tmp;

	tmp = redirs;
	while (tmp && fd != -1)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == INPUT)
		{
			fd = check_infile(redir->file, fd, iscommand);
			*ishdoc = 0;
		}
		else if (redir->type == HEREDOC)
		{
			fd = heredoc_loop(redir->file, fd, iscommand);
			*ishdoc = 1;
		}
		tmp = tmp->next;
	}
	return (fd);
}

int	redirect_infile(t_list *redirs, t_fds fds, int iscommand)
{
	int		fdin;
	int		ishdoc;
	(void)fds;

	ishdoc = 0;
	fdin = get_input(redirs, iscommand, &ishdoc);
	if (fdin == -1 || !fdin)
		return (fdin);
	if (ishdoc)
	{
		close(fdin);
		fdin = open(HDOC_TMP, O_RDWR, 0644);
	}
	if (dup2(fdin, fds.stdfdin) == -1)
		return (perror("redirect input"), -1);
	return (fdin);
}
