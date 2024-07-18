/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 03:08:16 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/07/17 03:08:16 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	heredoc_loop(char *limiter, int i)
{
	int		fd;
	char	*line;
	char	*filename;
	
	filename = ft_strjoin_f2("tmp-", ft_itoa(i));
	fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
	printf("%s, %i\n", filename, fd);
	free(filename);
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
	int		i;
	t_redir	*redir;

	i = 0;
	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		if (redir->type == HEREDOC)
		{
			fd = heredoc_loop(redir->file, i);
		}
		redirs = redirs->next;
		i++;
	}
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
	// while (redirs)
	// {
	// 	redir = redirs->content;
		
	// 	redirs = redirs->next;
	// }
	return (errcode);
}
