/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_fct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 21:23:34 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 21:51:30 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	and_proc(t_node *tree, int fd_in, int fd_out)
{
	extern t_id		g_pid;

	read_tree(tree->left, fd_in, fd_out);
	if (g_pid.built == 1)
		read_tree(tree->right, fd_in, fd_out);
	else if (g_pid.father != 0)
	{
		if (WIFEXITED(g_pid.id) && WEXITSTATUS(g_pid.id) == 0)
			read_tree(tree->right, fd_in, fd_out);
	}
	g_pid.father = 0;
	g_pid.id = 0;
	g_pid.built = -1;
}
