/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:58:20 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/09/07 19:01:57 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	print_var_env(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	printf("%s", var->key);
	if (var->value)
		printf("=%s", var->value);
	printf("\n");
}

void	print_var_exp(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	printf("declare -x %s", var->key);
	if (var->value)
		printf("=\"%s\"", var->value);
	printf("\n");
}
