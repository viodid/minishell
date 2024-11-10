/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 22:05:30 by dyunta            #+#    #+#             */
/*   Updated: 2024/10/23 20:22:28 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	free_split(char **tab);
static char	*join_split(char **split);
static char	*return_unexpanded_var(const char *value);
static char	*expand_var_in_str(const t_list *env, char *value, int errcode);

/*
 * Takes a string value (lexer token) and expands its variables accordingly.
*/
char	*expand_var_concat(const t_list *env, const char *value, int errcode)
{
	uint16_t	i;
	char		**split;
	char		*tmp_str;

	if (!ft_strchr(value, '$'))
		return (ft_strdup(value));
	split = ft_split(value, '$');
	i = 0;
	if (value[0] != '$')
		i++;
	while (split[i])
	{
		tmp_str = split[i];
		if (ft_isalpha(tmp_str[0]) || tmp_str[0] == '_' || tmp_str[0] == '?')
			split[i] = expand_var_in_str(env, tmp_str, errcode);
		else
			split[i] = return_unexpanded_var(tmp_str);
		free(tmp_str);
		i++;
	}
	return (join_split(split));
}

/*
 * This functions just returns the input string "value" with a dollar
 * sign "$" inserted at the beginning of the str.
*/
static char	*return_unexpanded_var(const char *value)
{
	char		*tmp_str;
	char		*output;
	uint32_t	len;

	len = ft_strlen(value) + 2;
	output = ft_calloc(len, sizeof(char));
	tmp_str = ft_strjoin("$", value);
	ft_strlcpy(output, tmp_str, len);
	free(tmp_str);
	return (output);
}

static char	*expand_var_in_str(const t_list *env, char *value, int errcode)
{
	uint16_t	i;
	char		*tmp_str;
	char		*var;

	if (!*value)
		return (value);
	tmp_str = value;
	i = 0;
	while (value[i] && (ft_isalnum(value[i]) || value[i] == '_'))
		i++;
	if (value[i] && i == 0 && value[i] == '?')
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
