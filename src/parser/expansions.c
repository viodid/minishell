/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:10:08 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/23 20:55:31 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*filter_quotes(const t_list *env, char *value, int errcode);

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
			((t_token *)token_list->content)->value = filter_quotes(env, value, errcode);
			free(tmp_str);
		}
		token_list = token_list->next;
	}
	return (head);
}

static char	*filter_quotes(const t_list *env, char *value, int errcode)
{
//	char		*str_start;
//	char		*str_mid;
//	char		*str_end;
//	uint32_t	size;
	int32_t	i;
	int32_t	offset;
	char		*tmp_str;
	char		*tmp_str_2;

	i = 0;
	offset = 0;
	while (value[i])
	{
		if (value[i] == '\'' || value[i] == '\0')
		{
			tmp_str = ft_substr(value, offset, i - offset);
			tmp_str_2 = tmp_str;
			tmp_str = expand_var_concat(env, tmp_str, errcode);
			free(tmp_str_2);
			tmp_str_2 = ft_substr(value, i, ft_strlen(value) - i);
			i = get_next_quote_idx(value, i);
			value = ft_strjoin_f12(tmp_str, tmp_str_2);
			offset = i + 1;
		}
		i++;
	}
	// TODO: handle loop quotes
//	if (ft_strchr(value, '\''))
//	{
//		str_start = ft_substr(value, 0, ft_strchr(value, '\'') - value);
//		str_mid = ft_substr(value, ft_strchr(value, '\'') - value, (ft_strrchr(value, '\'') - value));
//		str_end = ft_substr(value, ft_strrchr(value, '\'') - value, ft_strlen(value));
//		value = ft_strjoin_f12(expand_var_concat(env, str_start, errcode), str_mid);
//		free(str_start);
//		value = ft_strjoin_f12(value, expand_var_concat(env, str_end, errcode));
//		free(str_end);
//	}
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
