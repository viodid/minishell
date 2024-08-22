/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 03:08:16 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/08/22 14:18:23 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_loop(char *limiter)
{
	int		fd;
	char	*line;

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

int	heredocs(t_list *redirs)
{
	int		fd;
	int		ishdoclast;
	t_redir	*redir;
	t_list	*tmp;

	ishdoclast = 0;
	tmp = redirs;
	while (tmp)
	{
		redir = (t_redir *)tmp->content;
		if (redir->type == INPUT)
			ishdoclast = 0;
		else if (redir->type == HEREDOC)
		{
			fd = heredoc_loop(redir->file);
			ishdoclast = 1;
		}
		tmp = tmp->next;
	}
	if (!ishdoclast)
		return (unlink(HDOC_TMP), -2); //return fd of last input (open "file")
	return (fd);
}

int	redirect(t_list *redirs)
{
	int		errcode;
	int		fdhdoc;
	// int		fdin;
	// int		fdout;
	t_redir	*redir;
	(void)redir;
	(void)fdhdoc;

	//TODO finish making heredocs and start other redirections
	errcode = EXIT_SUCCESS;
	fdhdoc = heredocs(redirs);
	if (fdhdoc == -1)
		return (EXIT_FAILURE); //heredoc file couldnt be created
	
	return (errcode);
}
