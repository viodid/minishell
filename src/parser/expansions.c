/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:10:08 by dyunta            #+#    #+#             */
/*   Updated: 2024/09/10 21:45:22 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*expand_types(t_list *env, char *value, t_token_type type, int errcode);
static	char	*find_var(t_list *env, char *key, int errcode);
static char	*expand_var_quotes(t_list *env, char *value, int errcode);
static void	free_split(char **tab);
static char	*join_split(char **split);

void	execute_expansions(t_data *core)
{
	t_list			*cmds;
	t_list			*tokens;
	t_list			*redirs;
	t_token_type	type;

	cmds = core->line->cmds;
	while (cmds)
	{
		tokens = ((t_command *)cmds->content)->tokens;
		while (tokens)
		{
			type = ((t_token *)tokens->content)->type;
			if (type == VARIABLE || type == TILDE_EXPANSION || type == DOUBLE_QUOTE_STRING)
				//TODO: free previous str
				((t_token *)tokens->content)->value = expand_types(core->env, ((t_token *)tokens->content)->value, type, core->errcode);
			tokens = tokens->next;
		}
		redirs = ((t_command *)cmds->content)->redirs;
		while (redirs) {
			type = ((t_redir *) redirs->content)->token_type;
			if (type == VARIABLE || type == TILDE_EXPANSION || type == DOUBLE_QUOTE_STRING)
				//TODO: free previous str
				((t_redir *)redirs->content)->file = expand_types(core->env, ((t_redir *)redirs->content)->file, type, core->errcode);
			redirs = redirs->next;
		}
		cmds = cmds->next;
	}
}

static char	*expand_types(t_list *env, char *value, t_token_type type, int errcode)
{
	if (type == TILDE_EXPANSION)
		return(find_var(env, "HOME", errcode));
	if (type == VARIABLE)
		return (find_var(env, (value + 1), errcode));
	if (type == DOUBLE_QUOTE_STRING)
		return (expand_var_quotes(env, value, errcode));
	return (NULL);
}

/*
 * find_var finds the correct value in env list at key, allocates enough space for value and
 * returns it.
*/
static char	*find_var(t_list *env, char *key, int errcode)
{
	t_var	*var;
	char	*empty_str;

	if (ft_strncmp(key, "?", ft_strlen(key)) == 0)
		return (ft_itoa(errcode));

	while (env)
	{
		var = ((t_var *)env->content);
		if (ft_strncmp(key, var->key, ft_strlen(key)) == 0)
			return (ft_strdup(var->value));
		env = env->next;
	}
	empty_str = ft_calloc(1, 1);
	return (empty_str);
}

static char	*expand_var_quotes(t_list *env, char *value, int errcode)
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
	while(split[i])
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
