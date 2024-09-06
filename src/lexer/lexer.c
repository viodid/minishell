/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:12:28 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/06 21:15:45 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_list	*tokenizer(const char *user_input);
static char		*loop_readline(void);
static void		insert_token(char *value, t_list **token_list);
static char		*remove_odd_quotes(char *user_input);

t_list	*lexer(void)
{
	char	*user_input;
	t_list	*token_list;

	user_input = loop_readline();
	if (!*user_input)
		return (EXIT_SUCCESS);
	token_list = tokenizer(user_input);
	ft_lstiter(token_list, &print_token_list);
	if (errno)
		free_list(&token_list, &free_token);
	return (token_list);
}

static int32_t	get_str_size(const char *user_input, int32_t i)
{
	int32_t	idx;

	idx = i;
	if (ft_strchr("\"\'", user_input[i]) && user_input[i] != '\0')
		idx = get_end_quote_idx(user_input, i);
	if ((int)idx == -1)
	{
		send_error("syntax error: ", "unclosed quotes", -1);
		errno = ENOMSG;
		return (i);
	}
	return (idx);
}

static int	get_size_metachar(const char *user_input, uint32_t i)
{
	if (ft_strchr("<>", user_input[i]) && user_input[i] != '\0')
	{
		if ((ft_strncmp(&user_input[i], ">>", 2) == 0) || (ft_strncmp(&user_input[i], "<<", 2) == 0))
			return (2);
	}
	return (1);
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

	static char	*remove_odd_quotes(char *user_input)
{
	uint16_t	single_quotes;
	uint16_t	double_quotes;
	uint16_t	i;

	single_quotes = 0;
	double_quotes = 0;
	i = -1;
	while (user_input[++i])
	{
		if (user_input[i] == '\'')
			single_quotes++;
		else if (user_input[i] == '\"')
			double_quotes++;
	}
	if ((single_quotes % 2) == 1)
		user_input = handle_odd_quotes('\'', single_quotes, user_input);
	if ((double_quotes % 2) == 1)
		user_input = handle_odd_quotes('\"', double_quotes, user_input);
	return (user_input);
}

static void	insert_token(char *value, t_list **token_list)
{
	t_token		*token;

	if (ft_strchr(" \t\n\0", *value))
		return ;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = value;
	token->type = enum_token_value(value);
	ft_lstadd_back(token_list, ft_lstnew(token));
}

static char	*loop_readline(void)
{
	char		*tmp_str1;
	char		*tmp_str2;

	tmp_str1 = NULL;
	tmp_str2 = NULL;
	tmp_str1 = readline("minishell >");
	while (tmp_str1[ft_strlen(tmp_str1) - 1] == '\\')
	{
		tmp_str2 = ft_strtrim(tmp_str1, "\\");
		free(tmp_str1);
		tmp_str1 = ft_strjoin_f12(tmp_str2, readline(">"));
	}
	return (tmp_str1);
}
