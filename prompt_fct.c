/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 21:19:15 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 22:45:09 by lfouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*check_pwd(char **environ)
{
	t_env	*env;
	int		i;

	i = 0;
	env = init_env(environ);
	while (ft_strncmp("PWD=", env->environ[i], 4) && env->environ[i])
		i++;
	if (!env->environ[i])
		return (NULL);
	return (env->environ[i] + 4);
}

static char		*check_user(char **environ)
{
	t_env	*env;
	int		i;

	i = 0;
	env = init_env(environ);
	while (ft_strncmp("USER", env->environ[i], 4) && env->environ[i])
		i++;
	if (!env->environ[i])
		return ("guest");
	return (env->environ[i] + 5);
}

int				display_prompt(char **environ)
{
	char	*pwd;
	char	*user;

	pwd = check_pwd(environ);
	user = check_user(environ);
	ft_putstr("$ ");
	ft_putstr(user);
	ft_putstr(" ~");
	ft_putstr(pwd);
	ft_putstr(" > ");
	return ((int)(ft_strlen(user) + ft_strlen(pwd) + 7));
}
