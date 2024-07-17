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

int	heredocs(t_list *redirs)
{
	int		i;
	int		fd;
	char	*filename;
	t_redir	*redir;

	i = 0;
	while (redirs)
	{
		redir = (t_redir *)redirs->content;
		if (redir->type == HEREDOC)
		{
			filename = ft_strjoin_f2("tmp/", ft_itoa(i));
			fd = open(filename, O_CREAT);
			//TODO read term input and shove it line by line into tmp file
		}
		redirs = redirs->next;
	}
}

int	redirect(t_list *redirs)
{
	int		errcode;
	t_redir	*redir;
	//TODO finish making heredocs and start other redirections
	errcode = heredocs(redirs);
	while (redirs)
	{
		redir = redirs->content;
		
		redirs = redirs->next;
	}
	
}
