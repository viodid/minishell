/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 19:23:00 by dyunta            #+#    #+#             */
/*   Updated: 2024/08/25 20:41:31 by dyunta           ###   ########.fr       */
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
