/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:12:28 by dyunta            #+#    #+#             */
/*   Updated: 2024/08/26 20:14:43 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_list	*tokenizer(const char *user_input);
static char		*loop_readline(char metachar);
static void		insert_token(char *value, t_list **token_list);
static char		*remove_odd_quotes(char *user_input);

t_list	*lexer(void)
{
	char	*user_input;
	t_list	*token_list;

	user_input = loop_readline('\\');
	if (!*user_input)
		return (EXIT_SUCCESS);
	user_input = remove_odd_quotes(user_input);
	token_list = tokenizer(user_input);
	ft_lstiter(token_list, &print_token_list);
	return (token_list);
}

static t_list	*tokenizer(const char *user_input)
{
	const char	*metacharacters = " \"\'|&;()<>\t\n";
	char		*tmp_str;
	t_list		*token_list;
	uint32_t	offset;
	uint32_t	i;

	token_list = NULL;
	i = -1;
	offset = 0;
	while (++i <= ft_strlen(user_input))
	{
		if (ft_strchr(metacharacters, user_input[i]))
		{
			if (ft_strchr("\"\'", user_input[i]) && user_input[i] != '\0')
				i = get_end_quote_idx(user_input, i);
			if (!i)
				exit(EXIT_FAILURE);
			tmp_str = ft_substr(user_input, offset, i - offset);
			insert_token(tmp_str, &token_list);
			tmp_str = ft_substr(user_input, i, 1);
			insert_token(tmp_str, &token_list);
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

// TODO: handle heredoc
static char	*loop_readline(const char metachar)
{
	char		*tmp_str1;
	char		*tmp_str2;

	tmp_str1 = NULL;
	tmp_str2 = NULL;
	tmp_str1 = readline("minishell >");
	while (tmp_str1[ft_strlen(tmp_str1) - 1] == metachar)
	{
		tmp_str2 = ft_strtrim(tmp_str1, " \t\n");
		free(tmp_str1);
		tmp_str1 = ft_strjoin_f12(tmp_str2, readline(">"));
	}
	return (tmp_str1);
}
