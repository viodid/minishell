/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:12:28 by dyunta            #+#    #+#             */
/*   Updated: 2024/08/19 19:53:06 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

static char	*loop_readline(const char metachar);

t_list	*lexer(void)
{
	// const char	*metacharacters = " \t\n\\|&;()<>";
	char	*user_input;
	t_list	*token_list;

	user_input = loop_readline('\\');
	if (!*user_input)
		return (EXIT_SUCCESS);
	return (token_list);
}

static char	*loop_readline(const char metachar)
{
	char		*tmp_str1;
	char		*tmp_str2;

	tmp_str1 = NULL;
	tmp_str2 = NULL;
	tmp_str1 = readline("minishell >");
	while (TRUE)
	{
		tmp_str2 = ft_strtrim(tmp_str1, " ");
		free(tmp_str1);
		if (tmp_str2[ft_strlen(tmp_str2) - 1] != metachar)
			break ;
		tmp_str1 = ft_strjoin_f12(tmp_str2, readline(">"));
	}
	return (tmp_str2);
}

