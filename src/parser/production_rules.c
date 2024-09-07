/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:33:21 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/07 16:22:54 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

static t_pr_rule	*redirection(t_list **token_list, t_token *look_ahead)
{
	t_pr_rule	*pr_rule;
	t_list		*terminals_list;

	if (look_ahead->type != REDIRECTION)
		return (NULL);
	pr_rule = (t_pr_rule *) malloc(sizeof(t_pr_rule));
	if (!pr_rule)
		exit(EXIT_FAILURE);
	terminals_list = NULL;
	ft_lstadd_back(&terminals_list, ft_lstnew(look_ahead));
	pr_rule->terminals = terminals_list;
	look_ahead = get_next_token(token_list, look_ahead);
}

static t_pr_rule	*command(t_list **token_list, t_token *look_ahead)
{
	t_pr_rule	*pr_rule;
	t_list	*AST_list;
	t_AST	*AST;

	AST_list = NULL;
	create_AST_insert_list(token_list, look_ahead, &AST_list, &redirection);
	pr_rule = (t_pr_rule *) malloc(sizeof(t_pr_rule));
	if (!pr_rule)
		exit(EXIT_FAILURE);
	pr_rule->AST_nodes = AST_list;
	pr_rule->terminals = NULL;
	return (pr_rule);
}


static t_pr_rule	*full_command(t_list **token_list, t_token	*look_ahead)
{
	t_pr_rule	*pr_rule;
	t_list	*AST_list;
	t_AST	*AST;

	AST_list = NULL;
	create_AST_insert_list(token_list, look_ahead, &AST_list, &command);
	pr_rule = (t_pr_rule *) malloc(sizeof(t_pr_rule));
	if (!pr_rule)
		exit(EXIT_FAILURE);
	pr_rule->AST_nodes = AST_list;
	pr_rule->terminals = NULL;
	return (pr_rule);
}

t_AST	*RDP(t_list *token_list)
{
	t_AST	*AST;
	t_token	*look_ahead;

	look_ahead = (t_token *)token_list->content;
	AST = (t_AST *)malloc(sizeof(t_AST));
	if (!AST)
		exit(EXIT_FAILURE);
	AST->non_terminal = FULL_CMD;
	AST->production_rules = full_command(&token_list, look_ahead);
}



