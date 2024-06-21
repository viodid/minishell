/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 21:29:17 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/05/27 21:30:30 by kde-la-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_var(void *cont)
{
	t_var	*var;

	var = (t_var *)cont;
	printf("%s=%s\n", var->key, var->value);
}

t_list	*set_env(char **envp)
{
	int		i;
	char	*tmpenv;
	t_var	*var;
	t_list	*ret;

	i = -1;
	ret = NULL;
	while (envp[++i])
	{
		var = ft_calloc(1, sizeof(t_var));
		tmpenv = ft_strdup(envp[i]);
		var->key = ft_substr(tmpenv, 0, ft_strchr(tmpenv, '=') - tmpenv);
		free(tmpenv);
		tmpenv = ft_strdup(envp[i]);
		var->value = ft_strdup(ft_strchr(tmpenv, '=') + 1);
		free(tmpenv);
		ft_lstadd_back(&ret, ft_lstnew(var));
	}
	return (ret);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	core;
	(void)argc;
	(void)argv;

	core.envp = envp;
	core.envl = set_env(envp);
	while (1)
	{
		i = minishell(&core);
		if (i)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

