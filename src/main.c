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

char	*ft_getenv(char *key, char **envp)
{
	int		i;
	int		keylen;

	if (!envp)
		return (NULL);
	key = ft_strjoin(key, "=");
	keylen = ft_strlen(key);
	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(key, envp[i], keylen))
			return (free(key), ft_strchr(envp[i], '=') + 1);
	}
	return (free(key), NULL);
}

char	*get_key(char *var)
{
	int		i;
	char	*key;

	i = ft_strchr(var, '=') - var;
	var[i] = 0;
	key = ft_strdup(var);
	return (key);
}

t_list	*set_env(char **envp)
{
	int		i;
	char	*tmp;
	t_var	var;
	t_list	*ret;

	i = -1;
	ret = ft_lstnew(NULL);
	while (envp[++i])
	{
		var.key = get_key(envp[i]);
		printf("%s=", var.key);
		tmp = ft_strchr(envp[i], '=') + 1;
		//TODO solve value attribution problem for values
		if (tmp)
			var.value = ft_strdup(tmp);
		else
			var.value = NULL;
		printf("%s\n", var.value);
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

