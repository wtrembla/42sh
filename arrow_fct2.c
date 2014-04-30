/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_fct2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 17:50:07 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 21:52:11 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			clear_aff(t_historic **historic)
{
	if ((*historic)->copy->size)
	{
		apply_movebegin(historic);
		tputs(tgetstr("cd", NULL), 1, aff_c);
	}
}

void			display_comline(t_historic **historic)
{
	t_comline		*tmp;

	tmp = NULL;
	if ((*historic)->copy->size)
	{
		while ((*historic)->copy->comline)
		{
			tmp = (*historic)->copy->comline;
			(*historic)->copy->comline = (*historic)->copy->comline->right;
		}
		(*historic)->copy->comline = tmp;
		aff_str((*historic)->copy->line);
	}
	if (check_ending(tmp))
		tputs(tgetstr("do", NULL), 1, aff_c);
}

void			apply_arrowup(t_historic **historic)
{
	if ((*historic)->copy->up)
	{
		clear_aff(historic);
		(*historic)->copy = (*historic)->copy->up;
		display_comline(historic);
	}
}

void			apply_arrowdown(t_historic **historic)
{
	if ((*historic)->copy->down)
	{
		clear_aff(historic);
		(*historic)->copy = (*historic)->copy->down;
		display_comline(historic);
	}
}
