/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_set_unset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midoubih <midoubih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 15:25:42 by midoubih          #+#    #+#             */
/*   Updated: 2014/03/27 15:38:50 by midoubih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*skip_space(char *str)
{
	while (*str && *str == ' ')
		str++;
	return (str);
}

static int	env_add_elem(t_env *env, char *var)
{
	int		i;
	char	**tmp;

	i = ft_tablen(env->environ);
	tmp = ft_tabdup(env->environ, i + 1);
	tmp[i] = ft_strdup(var);
	del_tab(env->environ);
	env->environ = tmp;
	return (1);
}

int			setenv_fct(char *var)
{
	int		i;
	int		res;
	t_env	*env;
	char	**tmp;

	i = 0;
	res = 0;
	env = init_env(NULL);
	var = skip_space(var);
	tmp = ft_strsplit(var, '=');
	while (tmp[0] && env->environ[i])
	{
		if (!ft_strncmp(env->environ[i], tmp[0], ft_strlen(tmp[0])))
		{
			ft_strdel(&env->environ[i]);
			env->environ[i] = ft_strdup(var);
			res = 1;
		}
		++i;
	}
	if (!res && tmp[0])
		res = env_add_elem(env, var);
	del_tab(tmp);
	return (res);
}

int			unsetenv_fct(char *var)
{
	int		res;
	int		i;
	char	**env_ptr;

	i = 0;
	res = 0;
	var = skip_space(var);
	env_ptr = init_env(NULL)->environ;
	while (*var && env_ptr[i])
	{
		if (!ft_strncmp(env_ptr[i], var, ft_strlen(var)))
		{
			ft_strdel(&env_ptr[i]);
			res = 1;
			while (env_ptr[i + 1])
			{
				env_ptr[i] = env_ptr[i + 1];
				env_ptr[i + 1] = NULL;
				++i;
			}
		}
		++i;
	}
	return (res);
}
