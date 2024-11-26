/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dyunta <dyunta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 12:22:00 by dyunta            #+#    #+#             */
/*   Updated: 2024/11/26 19:34:02 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*construct_words(char *prompt, char *username, char *cwd)
{
	prompt = ft_strjoin_f1(prompt, GRN_BOLD);
	prompt = ft_strjoin_f1(prompt, username);
	prompt = ft_strjoin_f1(prompt, "@");
	prompt = ft_strjoin_f1(prompt, HOSTNAME);
	prompt = ft_strjoin_f1(prompt, RES);
	prompt = ft_strjoin_f1(prompt, ":");
	prompt = ft_strjoin_f1(prompt, BLU_BOLD);
	prompt = ft_strjoin_f1(prompt, cwd);
	prompt = ft_strjoin_f1(prompt, RES);
	return (ft_strjoin_f1(prompt, "$ "));
}

char	*get_prompt(t_list *env)
{
	char	*prompt;
	t_var	*content;
	char	*username;
	char	*cwd;

	prompt = (char *) ft_calloc(1, sizeof(char));
	if (!prompt)
		exit(EXIT_FAILURE);
	while (env)
	{
		content = (t_var *)env->content;
		if (!ft_strncmp(content->key, "USER", ft_strlen("USER")))
			username = content->value;
		else if (!ft_strncmp(content->key, "PWD", ft_strlen("PWD")))
			cwd = content->value;
		env = env->next;
	}
	return (construct_words(prompt, username, cwd));
}
