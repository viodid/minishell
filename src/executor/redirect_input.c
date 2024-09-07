/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 03:08:16 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/29 20:03:10 by kde-la-c         ###   ########.fr       */
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

int	get_input(t_list *redirs, int iscommand)
{
	int		fd;
	t_redir	*redir;
	t_list	*tmp;

	tmp = redirs;
	while (tmp && fd != -1)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == INPUT)
			fd = check_infile(redir->file, fd, iscommand);
		else if (redir->type == HEREDOC)
			fd = heredoc_loop(redir->file, fd, iscommand);
		tmp = tmp->next;
	}
	return (fd);
}

int	redirect_input(t_list *redirs, t_fds fds, int *stdinbak, int iscommand)
{
	int		fdin;
	(void)fds;

	fdin = get_input(redirs, iscommand);
	if (fdin == -1 || !fdin)
		return (fdin);
	*stdinbak = dup(fds.stdfdin); // this saves STDIN before redirection
	printf("fdin:%i bak:%i\n", fdin, *stdinbak);
	if (*stdinbak == -1 || dup2(fdin, fds.stdfdin) == -1)
	{
		perror("stdin backup");
		return (-1);
	}
	return (fdin);
}
