/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 21:31:07 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:20:26 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_fd_file_redir(char *name)
{
	int			fd;

	if ((fd = open(name, O_WRONLY | O_CREAT, S_IRWXU
					| S_IRWXG | S_IRWXO)) == -1)
		ft_error("redir_fct: cannt create stdout file");
	free(name);
	return (fd);
}

void		redir_proc(t_node *tree, int fd_in, int fd_out)
{
	fd_out = get_fd_file_redir(ft_strtrim(tree->left->word));
	read_tree(tree->right, fd_in, fd_out);
	close(fd_out);
}
