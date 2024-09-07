/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:26:12 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/07 16:02:49 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	create_AST_insert_list(t_list **token_list, t_token *look_ahead, t_list **AST_list, t_pr_rule* (*f)(t_list **, t_token *))
{
	t_AST	*AST;

	AST = (t_AST *)malloc(sizeof(t_AST));
	if (!AST)
		exit(EXIT_FAILURE);
	AST->non_terminal = CMD;
	AST->pr_rules = f(token_list, look_ahead);
	if (!(AST->pr_rules))
	{
		free(AST);
		return ;
	}
	ft_lstadd_back(AST_list, ft_lstnew(AST));
}