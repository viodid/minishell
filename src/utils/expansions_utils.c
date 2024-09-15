/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:05:30 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/16 00:07:40 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_split(char **tab);
static char	*join_split(char **split);
static char	*expand_var_in_str(t_list *env, char *value, int errcode);

char	*expand_var_concat(t_list *env, char *value, int errcode)
{
	uint16_t	i;
	char		**split;
	char		*tmp_str;

	if (!strchr(value, '$'))
		return (ft_strdup(value));
	split = ft_split(value, '$');
	i = 0;
	while (split[i])
	{
		tmp_str = split[i];
		if (ft_isalpha(tmp_str[0]))
		{
			split[i] = expand_var_in_str(env, tmp_str, errcode);
			free(tmp_str);
		}
		i++;
	}
	return (join_split(split));
}

static char	*expand_var_in_str(t_list *env, char *value, int errcode)
{
	uint16_t	i;
	char		*tmp_str;
	char		*var;

	if (!*value)
		return (value);
	tmp_str = value;
	i = 0;
	while (value[i] && ft_isalnum(value[i]))
		i++;
	var = (char *) ft_calloc(i + 1, 1);
	ft_strlcpy(var, value, i + 1);
	value = find_var(env, var, errcode);
	if (i < ft_strlen(tmp_str))
		value = ft_strjoin_f1(value, tmp_str + i);
	free(var);
	return (value);
}

static char	*join_split(char **split)
{
	int		i;
	char	*expanded_str;

	i = 1;
	expanded_str = ft_strdup(split[0]);
	while (split[i])
	{
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
