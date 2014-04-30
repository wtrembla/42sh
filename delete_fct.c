/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_fct.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 17:41:52 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/12 14:15:14 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			update_linecol(t_historic **historic)
{
	t_comline	*tmp;

	tmp = (*historic)->copy->comline;
	while (tmp->c != '\0')
		tmp = tmp->left;
	tmp = tmp->right;
	if (tmp)
	{
		while (tmp)
		{
			tmp->col = tmp->left->col + 1;
			tmp = tmp->right;
		}
	}
}

void			print_comline(t_historic **historic)
{
	tputs(tgetstr("cd", NULL), 1, aff_c);
	tputs(tgetstr("sc", NULL), 1, aff_c);
	aff_str((*historic)->copy->line + (*historic)->copy->comline->col
			- (*historic)->prompt + 1);
	tputs(tgetstr("rc", NULL), 1, aff_c);
}

void			apply_delete(t_historic **historic)
{
	int			win_size;
	t_comline	*tmp;

	if ((*historic)->copy->comline->c != '\0')
	{
		tmp = (*historic)->copy->comline->right;
		(*historic)->copy->comline = (*historic)->copy->comline->left;
		(*historic)->copy->comline->right = tmp;
		if (tmp)
			tmp->left = (*historic)->copy->comline;
		if ((win_size = check_beginning((*historic)->copy->comline)))
		{
			tputs(tgetstr("up", NULL), 1, aff_c);
			tputs(tgoto(tgetstr("ch", NULL), 0, win_size), 1, aff_c);
		}
		else
			tputs(tgetstr("le", NULL), 1, aff_c);
		tputs(tgetstr("dc", NULL), 1, aff_c);
		(*historic)->copy->size--;
		edit_line(historic);
		update_linecol(historic);
		print_comline(historic);
	}
}
