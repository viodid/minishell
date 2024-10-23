/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:10:08 by dyunta            #+#    #+#             */
/*   Updated: 2024/10/23 20:43:09 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char		*expand(const t_list *env, char *value, int errcode);
static t_list	*tokenizer(const char *user_input);

t_list	*execute_expansions(t_list *token_list, const t_list *env, int err)
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
			{
				value = ft_strjoin_f1(find_var(env, "HOME", err), value + 1);
				free(tmp_str);
				tmp_str = value;
			}
			((t_token *)token_list->content)->value = expand(env, value, err);
			free(tmp_str);
		}
		token_list = token_list->next;
	}
	return (head);
}

static t_list	*tokenizer(const char *user_input)
{
	char		*tmp_str;
	t_list		*token_list;
	int32_t		offset;
	int32_t		i;

	token_list = NULL;
	i = -1;
	offset = 0;
	while (++i <= (int32_t)ft_strlen(user_input))
	{
		if (ft_strchr("\'\"", user_input[i]))
		{
			tmp_str = ft_substr(user_input, offset, i - offset);
			insert_token(tmp_str, &token_list, TRUE);
			offset = i;
			i = get_str_size(user_input, i);
			tmp_str = ft_substr(user_input, offset, i - offset + 1);
			insert_token(tmp_str, &token_list, TRUE);
			offset = i + 1;
		}
	}
	return (token_list);
}

static void	expand_token_filter_quotes(t_list *token_list,
	const t_list *env, int errcode)
{
	char	*tmp_str;
	t_token	*token;

	while (token_list)
	{
		token = token_list->content;
		if (token->type == WORD || token->type == DOUBLE_QUOTES)
		{
			tmp_str = token->value;
			token->value = expand_var_concat(env, token->value, errcode);
			free(tmp_str);
		}
		if (token->type == DOUBLE_QUOTES || token->type == SINGLE_QUOTES)
		{
			tmp_str = token->value;
			token->value = remove_quotes(token->value);
			free(tmp_str);
		}
		token_list = token_list->next;
	}
}

static char	*expand(const t_list *env, char *value, int errcode)
{
	t_list	*tmp_token_list;
	t_list	*head_list;
	t_token	*token;

	tmp_token_list = tokenizer(value);
	head_list = tmp_token_list;
	expand_token_filter_quotes(tmp_token_list, env, errcode);
	value = ft_calloc(1, 1);
	while (tmp_token_list)
	{
		token = tmp_token_list->content;
		value = ft_strjoin_f1(value, token->value);
		tmp_token_list = tmp_token_list->next;
	}
	ft_lstclear(&head_list, &free_token);
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
