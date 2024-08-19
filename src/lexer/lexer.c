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

//t_list	*lexer(void)
//{
//	const char	*metacharacters = " \t\n\\|&;()<>";
//	char	*user_input;
//
//	user_input = readline("minishell >");
//}

char	*join_all_commands(void)
{
	char		*output_command;
	char		*user_input;
	char		*tmp_str;

	output_command = NULL;
	user_input = readline("minishell >");
	tmp_str = ft_strtrim(user_input, " ");
	output_command = ft_strdup(tmp_str);
	free(user_input);
	while (output_command[ft_strlen(output_command) - 1] == '\\')
		output_command = ft_strjoin_f12(output_command, readline("minishell >"));
	free(tmp_str);
	return (output_command);
}
