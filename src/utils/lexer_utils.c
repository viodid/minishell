/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:23:00 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/26 21:31:52 by dyunta           ###   ########.fr       */
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

uint8_t	is_identifier(const char *value)
{
	uint32_t	i;

	if (!ft_isalpha(*value) && *value != '_')
		return (FALSE);
	i = 1;
	while (value[i])
	{
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (FALSE);
		i++;
	}
	return (TRUE);
}

uint8_t	is_flag(const char *value)
{
	uint32_t	i;

	if (*value != '-')
		return (FALSE);
	i = 1;
	while (value[i])
	{
		if (!ft_isalpha(value[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

uint8_t	is_word_token(const char *value)
{
	int32_t	i;

	i = 0;
	while (value[i])
	{
		if (ft_strchr("\"\'", value[i]))
			i = get_str_size(value, i);
		if (value[i] && ft_strchr(" |&;()<>\t\n", value[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

char	*remove_quotes(char *str, t_token_type type)
{
	char	*tmp_str;
	char	*str_quote;

//	if (type != DOUBLE_QUOTE_STRING && type != SINGLE_QUOTE_STRING)
//		return (str);
	tmp_str = str;
	str_quote = (char *)ft_calloc(2, 1);
	ft_strlcpy(str_quote, str, 2);
	str = ft_strtrim(str, str_quote);
	free(tmp_str);
	free(str_quote);
	return (str);
}

int32_t	get_str_size(const char *user_input, int32_t i)
{
	int32_t	idx;

	idx = i;
	if (ft_strchr("\"\'", user_input[i]) && user_input[i] != '\0')
		idx = get_next_quote_idx(user_input, i);
	if (idx == -1)
	{
		if (!errno)
			send_error("syntax error: ", "unclosed quotes", -1);
		errno = 42;
		return (i);
	}
	return (idx);
}

int32_t	get_next_quote_idx(const char *str, int32_t i)
{
	char	quote_type;

	quote_type = str[i];
	while (str[++i])
	{
		if (str[i] == quote_type)
			return (i);
	}
	return (-1);
}

int	get_size_metachar(const char *user_input, uint32_t i)
{
	if ((ft_strncmp(&user_input[i], ">>", 2) == 0)
		|| (ft_strncmp(&user_input[i], "<<", 2) == 0))
		return (2);
	return (1);
}
