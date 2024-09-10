/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:10:08 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/09 20:35:35 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_types(t_list *env, char *value, t_token_type type, int errcode);
static	char	*find_var(t_list *env, char *key, int errcode);

void	execute_expansions(t_data *core)
{
	t_list			*cmds;
	t_list			*tokens;
	t_list			*redirs;
	t_token_type	type;

	cmds = core->line->cmds;
	while (cmds)
	{
		tokens = ((t_command *)cmds->content)->tokens;
		while (tokens)
		{
			type = ((t_token *)tokens->content)->type;
			if (type == VARIABLE || type == TILDE_EXPANSION || type == DOUBLE_QUOTE_STRING)
				//TODO: free previous str
				((t_token *)tokens->content)->value = expand_types(core->env, ((t_token *)tokens->content)->value, type, core->errcode);
			tokens = tokens->next;
		}
		redirs = ((t_command *)cmds->content)->redirs;
		while (redirs) {
			type = ((t_redir *) redirs->content)->token_type;
			if (type == VARIABLE || type == TILDE_EXPANSION || type == DOUBLE_QUOTE_STRING)
				//TODO: free previous str
				((t_redir *)redirs->content)->file = expand_types(core->env, ((t_redir *)redirs->content)->file, type, core->errcode);
			redirs = redirs->next;
		}
		cmds = cmds->next;
	}
}

static char	*expand_types(t_list *env, char *value, t_token_type type, int errcode)
{
	if (type == TILDE_EXPANSION)
		return(find_var(env, "HOME", errcode));
	if (type == VARIABLE)
		return (find_var(env, (value + 1), errcode));
	return (NULL);
}

static	char	*find_var(t_list *env, char *key, int errcode)
{
	t_var	*var;

	if (ft_strncmp(key, "?", ft_strlen(key)))
		return (ft_itoa(errcode));

	while (env)
	{
		var = ((t_var *)env->content);
		if (ft_strncmp(key, var->key, ft_strlen(key)) == 0)
			return (var->value);
		env = env->next;
	}
	return ("");
}
