/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 20:48:25 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:31:06 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_id		g_pid;

static char		**copy_env(char **environ)
{
	char	**env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	env = NULL;
	while (environ[i])
		i++;
	if (!(env = (char **)malloc(sizeof(char *) * (i + 1))))
		ft_error("copy_env: memory allocation failed");
	while (environ[j])
	{
		env[j] = ft_strdup(environ[j]);
		j++;
	}
	env[j] = '\0';
	return (env);
}

static char		**copy_path(void)
{
	char	*name;
	char	**path;

	if (!(name = getenv("PATH")))
		ft_error("copy_paths: variable PATH not found");
	path = ft_strsplit(name, ':');
	return (path);
}

static char		*copy_home(void)
{
	char	*home;

	if (!(home = getenv("HOME")))
		ft_error("copy_home: variable HOME not found");
	return (ft_strdup(home));
}

t_env			*init_env(char **environ)
{
	static t_env	*env = NULL;

	if (!env)
	{
		if (!(env = (t_env *)malloc(sizeof(t_env))))
			ft_error("init_env: memory allocation failed");
		env->environ = copy_env(environ);
		env->path = copy_path();
		env->home = copy_home();
	}
	return (env);
}

int				main(int ac, char **ag, char **environ)
{
	int			prompt;
	t_historic	*historic;

	(void)ac;
	(void)ag;
	g_pid.id = 0;
	g_pid.father = 0;
	g_pid.child = 0;
	g_pid.built = -1;
	if (tgetent(NULL, getenv("TERM")) < 1)
		ft_error("Improper environment.");
	set_term(1);
	prompt = display_prompt(environ);
	historic = init_historic(prompt);
	minishell(&historic);
	set_term(-1);
	return (0);
}
