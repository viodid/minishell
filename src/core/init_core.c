/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_core.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kde-la-c <kde-la-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 16:56:20 by kde-la-c          #+#    #+#             */
/*   Updated: 2024/11/26 16:51:34 by dyunta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_var	*split_var(char *var_brut)
{
	char	*tmpenv;
	t_var	*var;

	var = ft_calloc(1, sizeof(t_var));
	if (!var)
		return (NULL);
	tmpenv = ft_strdup(var_brut);
	if (!tmpenv)
		return (free(var), NULL);
	var->key = ft_substr(tmpenv, 0, ft_strchr(tmpenv, '=') - tmpenv);
	free(tmpenv);
	if (!var->key)
		return (free(var), NULL);
	tmpenv = ft_strdup(var_brut);
	if (!tmpenv)
		return (free(var->key), free(var), NULL);
	if (!ft_strchr(tmpenv, '='))
	{
		var->value = ft_strdup("");
		return (free(tmpenv), var);
	}
	var->value = ft_strdup(ft_strchr(tmpenv, '=') + 1);
	if (!var->value)
		return (free(tmpenv), free(var->key), free(var), NULL);
	return (free(tmpenv), var);
}

static int	set_shlvl(t_data *core)
{
	int		lvlnb;
	char	*newvar;
	t_var	*lvl;

	lvl = get_env(core, "SHLVL");
	if (!lvl && export_single(core, "SHLVL=1"))
		return (EXIT_FAILURE);
	lvlnb = ft_atoi(lvl->value);
	lvlnb += 1;
	newvar = ft_strjoin_f2("SHLVL=", ft_itoa(lvlnb));
	if (!newvar)
		return (EXIT_FAILURE);
	export_single(core, newvar);
	free(newvar);
	return (EXIT_SUCCESS);
}

static char	**set_basic_env(char *argv0)
{
	char	**ret;
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	ret = ft_calloc(4, sizeof(char *));
	if (!ret)
		return (free(cwd), NULL);
	ret[0] = ft_strjoin_f2("PWD=", cwd);
	if (!ret[0])
		return (free(ret), free(cwd), NULL);
	ret[1] = ft_strdup("SHLVL=0");
	if (!ret[1])
		return (ft_dfree((void **)ret), NULL);
	ret[2] = ft_strjoin("_=", argv0);
	if (!ret[2])
		return (ft_dfree((void **)ret), NULL);
	return (ret);
}

static t_list	*set_env(char **argv, char **envp)
{
	int		i;
	char	**env;
	t_list	*ret;
	t_var	*var;

	if (!envp || !envp[0])
		env = set_basic_env(argv[0]);
	else
		env = ft_matdup((void **)envp);
	if (!env)
		return (NULL);
	i = -1;
	ret = NULL;
	while (env[++i])
	{
		var = split_var(env[i]);
		if (!var)
			return (ft_lstclear(&ret, free_var), NULL);
		ft_lstadd_back(&ret, ft_lstnew(var));
	}
	ft_dfree((void **)env);
	return (ret);
}

/**
 * Initializes `core` with env variables, sets the shell level, allocates memory
 * for `core->line`, and initializes other variables.
 * 
 * @param core `t_data` struct to initialize.
 * @param argv sets the `_` env variable if no environment is provided.
 * @param envp contains the environment provided to Minishell.
 * 
 * @return `EXIT_SUCCESS` if all operations are successful.
 * `EXIT_FAILURE` if anything fails.
 */
int	init_core(t_data *core, char **argv, char **envp)
{
	core->env = set_env(argv, envp);
	if (!core->env)
		return (EXIT_FAILURE);
	if (set_shlvl(core))
		return (EXIT_FAILURE);
	core->line = NULL;
	core->errcode = 0;
	core->sv_stdin = -1;
	core->sv_stdout = -1;
	return (EXIT_SUCCESS);
}
