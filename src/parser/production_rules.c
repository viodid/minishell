/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   production_rules.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:33:21 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/07 15:16:06 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

static t_production_rules	*command(t_list **token_list, t_token *look_ahead)
{
	t_list	*AST_nodes;


}


static t_production_rules	*full_command(t_list **token_list, t_token	*look_ahead)
{
	t_production_rules	*production_rule;
	t_AST	*AST;
	t_list	*AST_list;

	production_rule = (t_production_rules *) malloc(sizeof(t_production_rules));
	if (!production_rule)
		exit(EXIT_FAILURE);
	AST_list = NULL;
	AST = (t_AST *)malloc(sizeof(t_AST));
	if (!AST)
		exit(EXIT_FAILURE);
	AST->non_terminal = CMD;
	AST->production_rules = command(token_list, look_ahead);
	if (!(AST->production_rules))
		return (NULL);
	ft_lstadd_back(&AST_list, ft_lstnew(AST));
	production_rule->AST_nodes = AST_list;
	production_rule->terminals = NULL;
	return (production_rule);
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



