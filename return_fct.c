/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 20:55:53 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:33:03 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			apply_return(t_historic **h)
{
	int			prompt;
	t_node		*tree;
	t_token		*comlist;

	tree = NULL;
	comlist = NULL;
	write(1, "\n", 1);
	if ((*h)->copy->size)
	{
		(*h)->historic = add_to_historic((*h)->historic, (*h)->copy->line);
		read_comline(&comlist, (*h)->copy->line);
		organize_com(&tree, &comlist, 1, 0);
		if (tree)
		{
			read_tree(tree, 0, 1);
			clear_tree(&tree);
		}
		prompt = display_prompt(NULL);
		del_comlist(comlist);
		del_copy((*h)->copy);
		(*h)->prompt = prompt;
		(*h)->copy = copy_historic((*h)->historic, prompt);
	}
	else
		display_prompt(NULL);
}
