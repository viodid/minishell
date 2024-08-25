/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:12:28 by dyunta            #+#    #+#             */
/*   Updated: 2024/08/25 18:58:56 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

static char	*loop_readline(char metachar);
t_list* tokenizer(const char* user_input);
static void insert_token(char* value, t_list** token_list);

t_list	*lexer(void)
{
	char	*user_input;
	t_list	*token_list;

	user_input = loop_readline('\\');
	if (!*user_input)
		return (EXIT_SUCCESS);
	token_list = tokenizer(user_input);
	return (token_list);
}

t_list	*tokenizer(const char* user_input)
{
	const char	*metacharacters = " |&;()<>\t\n";
	char		*tmp_str;
	t_list		*token_list;
	uint32_t	offset;
	uint32_t	i;

	token_list = NULL;
	i = 0;
	offset = 0;
	while (i <= ft_strlen(user_input))
	{
		if (ft_strchr(metacharacters, user_input[i]))
		{
			tmp_str = ft_substr(user_input, offset, i - offset);
			insert_token(tmp_str, &token_list);
			tmp_str = ft_substr(user_input, i, 1);
			insert_token(tmp_str, &token_list);
			offset = i + 1;
		}
		i++;
	}
	return (token_list);
}

static void insert_token(char* value, t_list** token_list)
{
	t_token		*token;

	if (ft_strchr(" \t\n\0", *value))
		return ;
	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		exit(EXIT_FAILURE);
	token->value = value;
	token->type = UNDEFINED;
	ft_lstadd_back(token_list, ft_lstnew(token));
}

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

