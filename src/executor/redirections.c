/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 03:08:16 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/26 14:53:04 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_loop(char *limiter, int fd)
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
	return (fd);
}

int	check_infile(char *infile, int fd)
{
	close(fd);
	if (!access(HDOC_TMP, R_OK))
		unlink(HDOC_TMP);
	fd = open(infile, O_RDONLY);
	if (fd == -1)
		perror(infile);
	return (fd);
}

int	get_input(t_list *redirs)
{
	int		fd;
	t_redir	*redir;
	t_list	*tmp;

	tmp = redirs;
	while (tmp && fd != -1)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == INPUT)
			fd = check_infile(redir->file, fd);
		else if (redir->type == HEREDOC)
			fd = heredoc_loop(redir->file, fd);
		tmp = tmp->next;
	}
	return (fd);
}

int	redirect_input(t_list *redirs, int *stdinbak)
{
	int		fdin;

	fdin = get_input(redirs);
	if (fdin == -1)
		return (fdin);
	*stdinbak = dup(STDIN_FILENO); // this saves STDIN before redirection
	if (*stdinbak == -1 || dup2(fdin, STDIN_FILENO) == -1)
		return (-1);
	return (fdin);
}
