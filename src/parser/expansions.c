/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:10:08 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/22 12:05:58 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_types(t_list *env, char *value,
				t_token_type type, int errcode);
static void	expansions_helper(t_list *redirs, t_list *tokens,
				t_list *env, int errcode);
static char	*expansions_helper_2(char *value, t_list *env,
				t_token_type type, int errcode);

void	execute_expansions(t_data *core)
{
	t_list			*cmds;
	t_list			*tokens;
	t_list			*redirs;

	cmds = core->line->cmds;
	while (cmds)
	{
		tokens = ((t_command *)cmds->content)->tokens;
		redirs = ((t_command *)cmds->content)->redirs;
		expansions_helper(redirs, tokens, core->env, core->errcode);
		cmds = cmds->next;
	}
}

static void	expansions_helper(t_list *redirs, t_list *tokens, t_list *env, int errcode)
{
	t_token_type	type;

	while (tokens)
	{
		type = ((t_token *)tokens->content)->type;
		if (type == WORD)
			((t_token *)tokens->content)->value = expansions_helper_2(
					((t_token *)tokens->content)->value, env, type, errcode);
		tokens = tokens->next;
	}
	while (redirs)
	{
		type = ((t_redir *) redirs->content)->token_type;
		if (type == REDIRECTION)
			((t_redir *)redirs->content)->file = expansions_helper_2(
					((t_redir *)redirs->content)->file, env, type, errcode);
		redirs = redirs->next;
	}
}

static char	*expansions_helper_2(char *value, t_list *env, t_token_type type, int errcode)
{
	char	*tmp_str;
	char	*output;

	tmp_str = value;
	output = expand_types(env, value, type, errcode);
	free(tmp_str);
	return (output);
}

static char	*expand_types(t_list *env, char *value,
	t_token_type type, int errcode)
{
	if (*value == '~')
		return (expand_var_concat(env,
				  ft_strjoin_f1(
						  find_var(env, "HOME", errcode), value + 1),
					  errcode));
	return (expand_var_concat(env, value, errcode));
}

/*
 * find_var finds the correct value in t_list *env at key, allocates enough
 * space for value and returns it.
*/
char	*find_var(t_list *env, char *key, int errcode)
{
	t_var	*var;
	char	*empty_str;

	if (ft_strncmp(key, "?", ft_strlen(key)) == 0)
		return (ft_itoa(errcode));
	while (env)
	{
		var = ((t_var *)env->content);
		if (ft_strlen(key) == ft_strlen(var->key)
		&& ft_strncmp(key, var->key, ft_strlen(key)) == 0)
			return (ft_strdup(var->value));
		env = env->next;
	}
	empty_str = ft_calloc(1, 1);
	return (empty_str);
}
