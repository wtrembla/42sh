/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirr_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 21:29:21 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:20:24 by lfouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		get_fd_file_redirr(char *name)
{
	int			fd;

	if ((fd = open(name, O_WRONLY | O_APPEND | O_CREAT, S_IRWXU
					| S_IRWXG | S_IRWXO)) == -1)
		ft_error("redir_fct: cannt create stdout file");
	free(name);
	return (fd);
}

void			redirr_proc(t_node *tree, int fd_in, int fd_out)
{
	fd_out = get_fd_file_redirr(ft_strtrim(tree->left->word));
	read_tree(tree->right, fd_in, fd_out);
	close(fd_out);
}
