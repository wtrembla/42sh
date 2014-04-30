/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scolon_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 18:14:35 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/12 19:13:47 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	scolon_proc(t_node *tree, int fd_in, int fd_out)
{
	read_tree(tree->left, fd_in, fd_out);
	read_tree(tree->right, fd_in, fd_out);
}
