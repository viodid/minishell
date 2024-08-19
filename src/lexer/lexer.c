/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 18:12:28 by dyunta            #+#    #+#             */
/*   Updated: 2024/08/19 19:15:07 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/minishell.h"

//t_list	*lexer(void)
//{
//	char	*user_input;
//
//	user_input = readline("minishell >");
//}

char	*join_all_commands(void)
{
	const char* metacharacters = " \t\n\\|&;()<>";
	char*	output_command;
	char*	user_input;
	char*	tmp_str;

	output_command = NULL;
	tmp_str = colored_output("minishell >", BLUE);
	user_input = readline("\\033[0;31mminishell >\\033[0;33m");

	return (output_command);
}
