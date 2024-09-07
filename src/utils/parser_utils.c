/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:26:12 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/07 19:08:22 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

//void	create_AST_insert_list(t_list **token_list, t_token *look_ahead, t_list **AST_list, t_pr_rule* (*f)(t_list **, t_token *))
//{
//	t_AST	*AST;
//
//	AST = (t_AST *)malloc(sizeof(t_AST));
//	if (!AST)
//		exit(EXIT_FAILURE);
//	AST->non_terminal = CMD;
//	AST->pr_rules = f(token_list, look_ahead);
//	if (!(AST->pr_rules))
//	{
//		free(AST);
//		return ;
//	}
//	ft_lstadd_back(AST_list, ft_lstnew(AST));
//}

t_token	*get_next_token(t_list *token_list, t_token *look_ahead)
{
	while (token_list->next)
	{
		if (token_list->content == look_ahead)
			return (token_list->content);
	}
	return (NULL);
}

t_redir	*create_redir(t_token *token)
{
	t_redir	*redir;

	redir = (t_redir *) malloc(sizeof(t_redir));
	if (!redir)
		exit(EXIT_FAILURE);
	if (ft_strncmp(token->value, "<", 2))
		redir->type = INPUT;
	else if (ft_strncmp(token->value, ">", 2))
		redir->type = OUTPUT;
	else if (ft_strncmp(token->value, ">>", 3))
		redir->type = APPEND;
	else if (ft_strncmp(token->value, "<<", 3))
		redir->type = HEREDOC;
	else
		exit(EXIT_FAILURE);
	redir->file = NULL;
	return (redir);
}
