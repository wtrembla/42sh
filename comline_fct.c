/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comline_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 21:04:39 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/04 16:02:57 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_comline	*add_char_to_comline(char c)
{
	t_comline	*elem;

	if (!(elem = (t_comline *)malloc(sizeof(t_comline))))
		ft_error("add_to_comline: memory allocation failed");
	elem->c = c;
	elem->col = 0;
	elem->right = NULL;
	elem->left = NULL;
	return (elem);
}

void		del_comline(t_comline *comline)
{
	t_comline	*tmp;

	if (comline)
	{
		while (comline->c != '\0')
			comline = comline->left;
		while (comline)
		{
			tmp = comline;
			comline = comline->right;
			tmp->right = NULL;
			tmp->left = NULL;
			free(tmp);
			tmp = NULL;
		}
	}
}
