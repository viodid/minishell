/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:05:30 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/13 19:05:31 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_split(char **tab);
static char	*join_split(char **split);

static char	*expand_var_quotes_2(t_list *env, char *value, int errcode)
{
	uint16_t	i;
	char		**split;
	char		*tmp_str;

	if (!*value)
		return (value);
	split = ft_split(value, ' ');
	// TODO: remove not alphanumeric characters from variable name
	tmp_str = split[0];
	split[0] = find_var(env, tmp_str, errcode);
	free(tmp_str);
	return (join_split(split));
}

char	*expand_var_quotes(t_list *env, char *value, int errcode)
{
	uint16_t	i;
	char		**split;
	char		*tmp_str;

	if (!*value)
		return (value);

	value = remove_quotes(value);
	split = ft_split(value, '$');
	i = 0;
	while (split[i])
	{
		tmp_str = split[i];
		if (ft_isalpha(tmp_str[0]))
		{
			split[i] = expand_var_quotes_2(env, tmp_str, errcode);
			free(tmp_str);
		}
		i++;
	}
	return (join_split(split));
}

static char	*join_split(char **split)
{
	int		i;
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
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
