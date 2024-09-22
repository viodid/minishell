/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:10:08 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/22 20:08:43 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
			if (*value == '~')
				value = ft_strjoin_f1(find_var(env, "HOME", errcode), value + 1);
			((t_token *)token_list->content)->value = expand_var_concat(env, value, errcode);
			free(tmp_str);
		}
		token_list = token_list->next;
	}
	return (head);
}

char	*filter_quotes(const t_list *env, char *value, int errcode)
{
	char		*str_start;
	char		*str_mid;
	char		*str_end;
	uint32_t	size;

	// TODO: handle loop quotes
	if (ft_strchr(value, '\''))
	{
		str_start = ft_substr(value, 0, ft_strchr(value, '\'') - value);
		str_mid = ft_substr(value, ft_strchr(value, '\'') - value, (ft_strrchr(value, '\'') - value));
		str_end = ft_substr(value, ft_strrchr(value, '\'') - value, ft_strlen(value));
		value = ft_strjoin_f12(expand_var_concat(env, str_start, errcode), str_mid);
		free(str_start);
		value = ft_strjoin_f12(value, expand_var_concat(env, str_end, errcode));
		free(str_end);
	}
	// TODO: remove quotes
	return (value);
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
