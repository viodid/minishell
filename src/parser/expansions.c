/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:10:08 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/22 14:11:27 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_types(char *value, const t_list *env, int errcode);

t_list	*execute_expansions(t_list *token_list, const t_list *env, int errcode)
{
	t_token_type	type;
	t_list			*head;
	char			*value;
	char			*tmp_str;

	head = token_list;
	while (token_list)
	{
		type = ((t_token *)token_list->content)->type;
		value = ((t_token *)token_list->content)->value;
		if (type == WORD)
		{
			tmp_str = value;
			((t_token *)token_list->content)->value = expand_types(value, env, errcode);
			free(tmp_str);
		}
		token_list = token_list->next;
	}
	return (head);
}

static char	*expand_types(char *value, const t_list *env, int errcode)
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
char	*find_var(const t_list *env, char *key, int errcode)
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
