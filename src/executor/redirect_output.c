/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_output.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 23:31:31 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/06 23:31:33 by kde-la-c         ###   ########.fr       */
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

