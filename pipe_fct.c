/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 18:16:23 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:13:42 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_left(t_node *tree, int fd_in, int fd_out, int *fd)
{
	close(fd[0]);
	dup2(fd[1], fd_out);
	read_tree(tree->left, fd_in, fd[1]);
	exit(EXIT_SUCCESS);
}

static void		ft_right(t_node *tree, int fd_in, int fd_out, int *fd)
{
	close(fd[1]);
	dup2(fd[0], fd_in);
	read_tree(tree->right, fd[0], fd_out);
	exit(EXIT_SUCCESS);
}

void			pipe_proc(t_node *tree, int fd_in, int fd_out)
{
	extern t_id		g_pid;
	int				fd_pipe[2];
	int				id;

	if (pipe(fd_pipe) == -1)
		ft_error("Broken pipe");
	g_pid.child = fork();
	if (g_pid.child == 0)
		ft_left(tree, fd_in, fd_out, fd_pipe);
	g_pid.father = fork();
	if (g_pid.father == 0)
		ft_right(tree, fd_in, fd_out, fd_pipe);
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	waitpid(g_pid.child, &id, 0);
	waitpid(g_pid.father, &g_pid.id, 0);
}
