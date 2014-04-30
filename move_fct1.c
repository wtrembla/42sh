/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fct1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/05 16:56:29 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:11:32 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		check_pos(t_historic **historic, int win_size, int test)
{
	if (test == 1 && (((*historic)->copy->comline->col + 1)
						>= (win_size + (*historic)->prompt)))
		return (1);
	else if (test == 2 && (((*historic)->copy->comline->col + 1) >= win_size))
		return (1);
	else if (test == -1 && ((*historic)->copy->size
							- (*historic)->copy->comline->col
							+ (*historic)->prompt + 1) >= win_size)
		return (1);
	else if (test == -2 && (((*historic)->copy->size
						- (*historic)->copy->comline->col
						+ (*historic)->prompt + 1) % win_size
							+ ((*historic)->copy->comline->col + 1) % win_size)
							>= win_size)
	{
		return (1);
	}
	return (0);
}

void			apply_moveup(t_historic **historic)
{
	int				col;
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	if (check_pos(historic, size.ws_col, 1))
	{
		tputs(tgetstr("up", NULL), 1, aff_c);
		col = (*historic)->copy->comline->col - size.ws_col;
		while ((*historic)->copy->comline->col != col)
			(*historic)->copy->comline = (*historic)->copy->comline->left;
	}
	else if (check_pos(historic, size.ws_col, 2)
			&& (*historic)->copy->comline->left)
	{
		tputs(tgetstr("up", NULL), 1, aff_c);
		tputs(tgoto(tgetstr("ch", NULL), 0, (*historic)->prompt), 1, aff_c);
		while ((*historic)->copy->comline->c != '\0')
			(*historic)->copy->comline = (*historic)->copy->comline->left;
	}
}

void			apply_movedown(t_historic **historic)
{
	int				col;
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	if (check_pos(historic, size.ws_col, -1))
	{
		tputs(tgetstr("do", NULL), 1, aff_c);
		tputs(tgoto(tgetstr("ch", NULL), 0, (*historic)->copy->comline->col
					% size.ws_col + 1), 1, aff_c);
		col = (*historic)->copy->comline->col + size.ws_col;
		while ((*historic)->copy->comline->col != col)
			(*historic)->copy->comline = (*historic)->copy->comline->right;
	}
	else if (check_pos(historic, size.ws_col, -2)
			&& (*historic)->copy->comline->right->right)
	{
		tputs(tgetstr("do", NULL), 1, aff_c);
		while ((*historic)->copy->comline->right)
			(*historic)->copy->comline = (*historic)->copy->comline->right;
		tputs(tgoto(tgetstr("ch", NULL), 0, (*historic)->copy->comline->col
					% size.ws_col + 1), 1, aff_c);
	}
}

void			apply_movenext(t_historic **historic)
{
	t_comline	*tmp;

	tmp = (*historic)->copy->comline;
	if (tmp->c == ' ')
		tmp = tmp->right;
	while (tmp && tmp->c != ' ')
		tmp = tmp->right;
	while (tmp && tmp->c == ' ')
		tmp = tmp->right;
	if (tmp)
		tmp = tmp->left;
	if (tmp && tmp->c == ' ')
	{
		while ((*historic)->copy->comline->col != tmp->col)
		{
			tputs(tgetstr("nd", NULL), 1, aff_c);
			(*historic)->copy->comline = (*historic)->copy->comline->right;
			if (check_ending((*historic)->copy->comline))
				tputs(tgetstr("do", NULL), 1, aff_c);
		}
	}
}

void			apply_moveprev(t_historic **historic)
{
	struct winsize	size;
	t_comline		*tmp;

	ioctl(0, TIOCGWINSZ, &size);
	tmp = (*historic)->copy->comline;
	if (tmp->c != '\0')
	{
		while (tmp->c != '\0' && tmp->c == ' ')
			tmp = tmp->left;
		while (tmp->c != '\0' && tmp->c != ' ')
			tmp = tmp->left;
		while ((*historic)->copy->comline->col != tmp->col)
		{
			(*historic)->copy->comline = (*historic)->copy->comline->left;
			if (check_beginning((*historic)->copy->comline))
			{
				tputs(tgetstr("up", NULL), 1, aff_c);
				tputs(tgoto(tgetstr("ch", NULL), 0, size.ws_col), 1, aff_c);
			}
			else
				tputs(tgetstr("le", NULL), 1, aff_c);
		}
	}
}
