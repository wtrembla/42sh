/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 21:25:23 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:18:03 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	or_proc(t_node *tree, int fd_in, int fd_out)
{
	extern t_id		g_pid;

	read_tree(tree->left, fd_in, fd_out);
	if (WIFSIGNALED(g_pid.id) || g_pid.built == 0)
		read_tree(tree->right, fd_in, fd_out);
	else if (g_pid.father != 0)
	{
		if (WIFEXITED(g_pid.id) && WEXITSTATUS(g_pid.id) > 0)
			read_tree(tree->right, fd_in, fd_out);
	}
	g_pid.father = 0;
	g_pid.id = 0;
	g_pid.built = -1;
}
