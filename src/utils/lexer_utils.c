/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:23:00 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/09 22:06:21 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*handle_odd_quotes(char quote, uint16_t total_quotes, char *str)
{
	char		*output_str;
	uint16_t	quote_n;
	uint16_t	str_len;

	str_len = ft_strlen(str);
	output_str = (char *) malloc(str_len - 1);
	if (!output_str)
		exit(EXIT_FAILURE);
	quote_n = 0;
	while (*str)
	{
		if (*str == quote)
		{
			quote_n++;
			if (total_quotes != quote_n)
				*output_str++ = *str;
		}
		else
			*output_str++ = *str;
		str++;
	}
	*output_str = '\0';
	free(str - str_len);
	return (output_str - (str_len - 1));
}

int32_t	get_end_quote_idx(const char *str, int32_t i)
{
	char	quote_type;

	quote_type = str[i];
	while (str[++i])
	{
		if (str[i] == quote_type)
			return (i + 1);
	}
	return (-1);
}

t_token_type	enum_token_value(const char *value)
{
	if (ft_strchr("<>", *value))
		return (REDIRECTION);
	else if (*value == '\'')
		return (SINGLE_QUOTE_STRING);
	else if (*value == '\"')
		return (DOUBLE_QUOTE_STRING);
	else if (*value == '$')
		return (VARIABLE);
	else if (*value == '~')
		return (TILDE_EXPANSION);
	else if (*value == '|')
		return (PIPE);
	else if (*value == '-')
		return (FLAG); // TODO: stronger FLAG checker
	else if (ft_isalnum(*value))
		return (IDENTIFIER); // TODO: stronger IDENTIFIER checker
	if (!errno)
		send_error("syntax error near unexpected token: ", (char *)value, 1);
	errno = 42;
	return (-1);
}

int32_t	get_str_size(const char *user_input, int32_t i)
{
	int32_t	idx;

	idx = i;
	if (ft_strchr("\"\'", user_input[i]) && user_input[i] != '\0')
		idx = get_end_quote_idx(user_input, i);
	if (idx == -1)
	{
		send_error("syntax error: ", "unclosed quotes", -1);
		errno = 42;
		return (i);
	}
	return (idx);
}

int	get_size_metachar(const char *user_input, uint32_t i)
{
	if (ft_strchr("<>", user_input[i]) && user_input[i] != '\0')
	{
		if ((ft_strncmp(&user_input[i], ">>", 2) == 0)
			|| (ft_strncmp(&user_input[i], "<<", 2) == 0))
			return (2);
	}
	return (1);
}
