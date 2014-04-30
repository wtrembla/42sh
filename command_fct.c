/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 19:45:55 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:24:20 by lfouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		del_argv(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		ft_strdel(&argv[i]);
		i++;
	}
	free(argv);
	argv = NULL;
}

char			*check_command(char *command)
{
	char	*tmp;
	int		i;
	int		ret;
	t_env	*env;

	env = init_env(NULL);
	tmp = ft_strdup(command);
	if (command[0] == '/' && !(ret = check_path(command)))
		return (tmp);
	else
	{
		i = -1;
		while (env->path[++i])
		{
			ft_strdel(&tmp);
			tmp = build_path(env->path[i], command);
			if (!(ret = check_path(tmp)))
				return (tmp);
		}
	}
	improper_path(ret, command);
	ft_strdel(&tmp);
	return (NULL);
}

static void		str_clean_replace(char **s1, char *s2)
{
	ft_strdel(s1);
	*s1 = s2;
}

int				command_proc(char *command, int fd_in, int fd_out)
{
	char			**argv;
	char			*tmp;
	extern t_id		g_pid;

	g_pid.id = 0;
	g_pid.father = 0;
	argv = ft_strsplit(command, ' ');
	if ((tmp = check_command(argv[0])))
	{
		str_clean_replace(&argv[0], tmp);
		if ((g_pid.father = fork()) == -1)
			ft_error("command_proc: no child process created");
		if (g_pid.father > 0)
			wait(&g_pid.id);
		if (!g_pid.father)
		{
			fd_in = (fd_in == -3) ? get_fd_file_redil(0) : fd_in;
			dup2(fd_in, 0);
			dup2(fd_out, 1);
			if (execve(argv[0], argv, init_env(NULL)->environ) == -1)
				ft_putjoin("42sh: command not found: ", argv[0]);
		}
	}
	del_argv(argv);
	return (1);
}
