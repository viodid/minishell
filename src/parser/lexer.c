/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:12:28 by dyunta            #+#    #+#             */
/*   Updated: 2024/11/26 21:52:46 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_list		*tokenizer(const char *user_input);
static char			*loop_readline(t_data *core);
static t_token_type	enum_token_value(const char *value, int parse_quotes);

t_list	*lexer(t_data *core)
{
	char	*user_input;
	t_list	*token_list;

	user_input = loop_readline(core);
	if (!*user_input)
	{
		errno = 42;
		return (free(user_input), NULL);
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
	int32_t		offset;
	int32_t		i;
	uint8_t		size_metachar;

	token_list = NULL;
	i = -1;
	offset = 0;
	while (++i <= (int32_t)ft_strlen(user_input))
	{
		if (ft_strchr("\"\'", user_input[i]))
			i = get_str_size(user_input, i);
		if (ft_strchr(METACHARACTERS, user_input[i]))
		{
			tmp_str = ft_substr(user_input, offset, i - offset);
			insert_token(tmp_str, &token_list, FALSE);
			size_metachar = get_size_metachar(user_input, i);
			tmp_str = ft_substr(user_input, i, size_metachar);
			insert_token(tmp_str, &token_list, FALSE);
			i += size_metachar - 1;
			offset = i + 1;
		}
	}
	return (token_list);
}

void	insert_token(char *value, t_list **token_list, int parse_quotes)
{
	t_token		*token;

	if (!*value || ft_strchr(" \t\n", *value))
	{
		free(value);
		return ;
	}
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->type = enum_token_value(value, parse_quotes);
	token->value = value;
	ft_lstadd_back(token_list, ft_lstnew(token));
}

static t_token_type	enum_token_value(const char *value, int parse_quotes)
{
	if (ft_strchr("<>", *value))
		return (REDIRECTION);
	if (*value == '|')
		return (PIPE);
	if (parse_quotes && *value == '\'')
		return (SINGLE_QUOTES);
	if (parse_quotes && *value == '\"')
		return (DOUBLE_QUOTES);
	if (is_word_token(value))
		return (WORD);
	if (!errno)
		send_error("syntax error near unexpected token: ", (char *)value, 1);
	errno = 42;
	return (-1);
}

static char	*loop_readline(t_data *core)
{
	char	*tmp_str1;
	char	*tmp_str2;
	char	*prompt;

	tmp_str1 = NULL;
	tmp_str2 = NULL;
	signal_handler(INTER);
	prompt = get_prompt(core->env);
	tmp_str1 = readline(prompt);
	free(prompt);
	while (tmp_str1 && tmp_str1[0] && tmp_str1[ft_strlen(tmp_str1) - 1] == '\\')
	{
		tmp_str2 = ft_strtrim(tmp_str1, "\\");
		free(tmp_str1);
		tmp_str1 = ft_strjoin_f12(tmp_str2, readline("> "));
	}
	if (tmp_str1 == NULL)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	return (tmp_str1);
}
