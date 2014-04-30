/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_fct1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/04 19:14:40 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/07 19:56:16 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_ending(t_comline *comline)
{
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	if (((comline->col + 1) % (size.ws_col)) == 0)
		return (1);
	else
		return (0);
}

int		check_beginning(t_comline *comline)
{
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	if ((comline->col % size.ws_col) == size.ws_col - 2)
		return (size.ws_col);
	else
		return (0);
}

void	apply_arrowright(t_historic **historic)
{
	if ((*historic)->copy->comline->right)
	{
		(*historic)->copy->comline = (*historic)->copy->comline->right;
		tputs(tgetstr("nd", NULL), 1, aff_c);
		if (check_ending((*historic)->copy->comline))
		{
			tputs(tgetstr("cr", NULL), 1, aff_c);
			tputs(tgetstr("do", NULL), 1, aff_c);
		}
	}
}

void	apply_arrowleft(t_historic **historic)
{
	int		win_size;

	if ((*historic)->copy->comline->left)
	{
		(*historic)->copy->comline = (*historic)->copy->comline->left;
		if ((win_size = check_beginning((*historic)->copy->comline)))
		{
			tputs(tgetstr("up", NULL), 1, aff_c);
			tputs(tgoto(tgetstr("ch", NULL), 0, win_size), 1, aff_c);
		}
		else
			tputs(tgetstr("le", NULL), 1, aff_c);
	}
}
