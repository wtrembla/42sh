/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redil_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 21:27:26 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:20:14 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		free_tab_redil(char **tab)
{
	int			i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int				get_fd_file_redil(int status)
{
	int			fd;

	if (status)
	{
		if ((fd = open(".tmp_redil", O_WRONLY | O_APPEND | O_CREAT, S_IRWXU
						| S_IRWXG | S_IRWXO)) == -1)
			ft_error("redil_fct: cannt create .tmp_redil");
		else
			return (fd);
	}
	else
	{
		if ((fd = open(".tmp_redil", O_RDONLY)) == -1)
			ft_error("redil_fct: cannt open .tmp_redil");
		else
			return (fd);
	}
	return (1);
}

int				remove_file_redil(void)
{
	char		**cmd;
	char		*path_cmd;
	t_env		*env;
	pid_t		father;

	env = init_env(NULL);
	cmd = ft_strsplit("rm -rf .tmp_redil", ' ');
	if ((path_cmd = check_command(cmd[0])) == NULL)
		ft_error("redil_fct: cannt find rm path");
	if ((father = fork()) == -1)
		ft_error("redil_fct: no child process created");
	else
	{
		if (father > 0)
			wait(0);
		if (father == 0)
		{
			if (execve(path_cmd, cmd, env->environ) == -1)
				ft_error("redil_fct: cannt remove .tmp_redil");
		}
	}
	free_tab_redil(cmd);
	free(path_cmd);
	return (1);
}

static int		ft_write_redil_file(char *name, int fd_out)
{
	int			ret;
	int			fd_in;
	char		*line;

	if ((fd_in = open(name, O_RDONLY)) == -1)
		return (0);
	else
	{
		while ((ret = get_next_line(fd_in, &line)) > 0)
		{
			ft_putstr_fd(line, fd_out);
			ft_putstr_fd("\n", fd_out);
			free(line);
		}
		if (ret == -1)
			return (0);
		close(fd_in);
		free(name);
		return (1);
	}
	return (1);
}

void			redil_proc(t_node *tree, int fd_in, int fd_out)
{
	fd_in = get_fd_file_redil(1);
	if (!ft_write_redil_file(ft_strtrim(tree->left->word), fd_in))
		return ;
	close(fd_in);
	read_tree(tree->right, -3, fd_out);
	remove_file_redil();
}
