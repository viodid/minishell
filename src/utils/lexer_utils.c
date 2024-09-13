/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:23:00 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/13 19:04:43 by dyunta           ###   ########.fr       */
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

char	*remove_quotes(char *str)
{
	char	*tmp_str;
	char	*str_quote;

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
