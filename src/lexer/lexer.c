/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:12:28 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/13 20:58:57 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_list	*tokenizer(const char *user_input);
static char		*loop_readline(void);
static void		insert_token(char *value, t_list **token_list);
static char		*remove_odd_quotes(char *user_input);
static t_token_type	enum_token_value(const char *value);

t_list	*lexer(void)
{
	char	*user_input;
	t_list	*token_list;

	user_input = loop_readline();
	if (!*user_input)
	{
		free(user_input);
		return (EXIT_SUCCESS);
	}
	token_list = tokenizer(user_input);
	add_history(user_input);
	free(user_input);
	if (errno)
		ft_lstclear(&token_list, &free_token);
	return (token_list);
}

static t_list	*tokenizer(const char *user_input)
{
	char		*tmp_str;
	t_list		*token_list;
	uint32_t	offset;
	int32_t		i;
	uint8_t		size_metachar;

	token_list = NULL;
	i = -1;
	offset = 0;
	while (++i <= (int32_t)ft_strlen(user_input))
	{
		if (ft_strchr(METACHARACTERS, user_input[i]))
		{
			i = get_str_size(user_input, i);
			tmp_str = ft_substr(user_input, offset, i - offset);
			insert_token(tmp_str, &token_list);
			size_metachar = get_size_metachar(user_input, i);
			tmp_str = ft_substr(user_input, i, size_metachar);
			insert_token(tmp_str, &token_list);
			i += size_metachar - 1;
			offset = i + 1;
		}
	}
	return (token_list);
}

static void	insert_token(char *value, t_list **token_list)
{
	t_token		*token;

	if (ft_strchr(" \t\n", *value))
	{
		free(value);
		return ;
	}
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->type = enum_token_value(value);
	if (token->type == DOUBLE_QUOTE_STRING || token->type == SINGLE_QUOTE_STRING)
		token->value = remove_quotes(value);
	else
		token->value = value;
	ft_lstadd_back(token_list, ft_lstnew(token));
}

static t_token_type	enum_token_value(const char *value)
{
	if (ft_strchr("<>", *value))
		return (REDIRECTION);
	if (*value == '\'')
		return (SINGLE_QUOTE_STRING);
	if (*value == '\"')
		return (DOUBLE_QUOTE_STRING);
	if (*value == '$')
		return (VARIABLE);
	if (*value == '~')
		return (TILDE_EXPANSION);
	if (*value == '|')
		return (PIPE);
	if (*value == '-')
		return (FLAG); // TODO: stronger FLAG checker
	if (ft_isalnum(*value))
		return (IDENTIFIER); // TODO: stronger IDENTIFIER checker
	if (!errno)
		send_error("syntax error near unexpected token: ", (char *)value, 1);
	errno = 42;
	return (-1);
}

static char	*loop_readline(void)
{
	char		*tmp_str1;
	char		*tmp_str2;

	tmp_str1 = NULL;
	tmp_str2 = NULL;
	tmp_str1 = readline("minishell > ");
	while (tmp_str1[ft_strlen(tmp_str1) - 1] == '\\')
	{
		tmp_str2 = ft_strtrim(tmp_str1, "\\");
		free(tmp_str1);
		tmp_str1 = ft_strjoin_f12(tmp_str2, readline("> "));
	}
	return (tmp_str1);
}
