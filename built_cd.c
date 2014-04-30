/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 18:46:58 by lfouquet          #+#    #+#             */
/*   Updated: 2014/03/27 21:59:02 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*get_true_path(char *path, t_env *env)
{
	char		*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	if (!ft_strcmp(path, "-"))
	{
		if ((pwd = (seek_env("OLDPWD="))))
		{
			pwd += ft_strlen("OLDPWD=");
			ft_putendl(pwd);
			return (pwd);
		}
	}
	else if (*path == '~')
		path = ft_strjoin(env->home, path + 1);
	else if (*path != '/')
		path = seek_true_path(path, pwd);
	return (path);
}

static int		check_cd_path(char **path, char **tab)
{
	int			nb_path;
	int			opt_p;

	nb_path = 0;
	opt_p = 0;
	while (*tab && nb_path < 2)
	{
		if (nb_path > 0 && (!ft_strcmp(*tab, "-P")
							|| !ft_strcmp(*tab, "-L")))
			return (-1);
		else if (!ft_strcmp(*tab, "-P"))
			opt_p = 1;
		else if (*tab != '\0' && ft_strcmp(*tab, "-P")
				&& ft_strcmp(*tab, "-L"))
		{
			*path = *tab;
			++nb_path;
		}
		++tab;
	}
	if (nb_path > 1)
		return (-1);
	return (0 + opt_p);
}

static int		change_directory(char **path, t_env *env)
{
	int		ret;
	char	*complete_path;

	ret = 0;
	if (!**path || !ft_strcmp(*path, "--"))
		complete_path = ft_strdup(env->home);
	else
		complete_path = get_true_path(*path, env);
	if (!complete_path || ((ret = chdir(complete_path)) == -1))
	{
		ft_putstr("cd: no such file or directory: ");
		ft_putendl(*path);
	}
	*path = complete_path;
	return (ret);
}

static void		update_env(char *path, char *oldpwd, t_env *env)
{
	int		i;
	char	**env_ptr;

	i = 0;
	env_ptr = env->environ;
	while (env_ptr[i])
	{
		if (!ft_strncmp(env_ptr[i], "OLDPWD=", 7))
		{
			ft_strdel(&env_ptr[i]);
			env_ptr[i] = ft_strjoin("OLDPWD=", oldpwd);
		}
		if (!ft_strncmp(env_ptr[i], "PWD=", 4))
		{
			ft_strdel(&env_ptr[i]);
			env_ptr[i] = ft_strjoin("PWD=", path);
		}
		i++;
	}
}

int				cd_fct(char *path)
{
	int			opt_p;
	char		*oldpwd;
	char		**tmp;
	t_env		*env;

	tmp = ft_strsplit(path, ' ');
	if ((opt_p = check_cd_path(&path, tmp)) < 0)
	{
		ft_putstr("cd: arguments invalid");
		del_tab(tmp);
		path = NULL;
		return (0);
	}
	oldpwd = NULL;
	oldpwd = getcwd(oldpwd, 0);
	env = init_env(NULL);
	if (change_directory(&path, env) != -1)
		update_env(path, oldpwd, env);
	else
		return (0);
	del_tab(tmp);
	return (1);
}
