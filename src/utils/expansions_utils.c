/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:05:30 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/10 22:06:26 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_split(char **tab);
static char	*join_split(char **split);

char	*expand_var_quotes(t_list *env, char *value, int errcode)
{
	uint16_t	i;
	char		**split;
	char		*tmp_str;

	if (!*value)
		return (value);
	split = ft_split(value + 1, ' ');
	i = 0;
	while (split[i])
	{
		tmp_str = split[i];
		if (tmp_str[0] == '$')
		{
			split[i] = find_var(env, tmp_str + 1, errcode);
			free(tmp_str);
		}
		i++;
	}
	return (join_split(split));
}

static char	*join_split(char **split)
{
	size_t	i;
	char	*expanded_str;
	char	*space;

	i = 1;
	expanded_str = ft_strdup(split[0]);
	while (split[i])
	{
		space = ft_calloc(2, 1);
		ft_strlcpy(space, " ", 2);
		expanded_str = ft_strjoin_f12(expanded_str, space);
		expanded_str = ft_strjoin_f1(expanded_str, split[i]);
		i++;
	}
	free_split(split);
	return (expanded_str);
}

static void	free_split(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
