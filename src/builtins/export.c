/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42Madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 15:21:10 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/06/19 15:21:10 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	export(t_data *core, char **var)
{
	char	*envvar;

	envvar = ft_getenv(var[0], core->envp);
}
