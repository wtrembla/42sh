/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 16:23:53 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 22:33:53 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	edit_line(t_historic **historic)
{
	char		*line;
	int			i;
	int			size;
	t_comline	*tmp;

	i = 0;
	tmp = (*historic)->copy->comline;
	while (tmp->c != '\0')
		tmp = tmp->left;
	tmp = tmp->right;
	size = (*historic)->copy->size;
	if (!(line = (char *)malloc(sizeof(char) * (size + 1))))
		ft_error("edit_line: memory allocation failed.");
	while (i < size)
	{
		line[i] = tmp->c;
		tmp = tmp->right;
		i++;
	}
	line[i] = '\0';
	ft_strdel(&(*historic)->copy->line);
	(*historic)->copy->line = line;
}

void	apply_edit(t_historic **historic, char c)
{
	t_comline	*ptmp;
	t_comline	*tmp;

	ptmp = NULL;
	tmp = (*historic)->copy->comline->right ?
		(*historic)->copy->comline->right : NULL;
	(*historic)->copy->comline->right = add_char_to_comline(c);
	ptmp = (*historic)->copy->comline;
	(*historic)->copy->comline = (*historic)->copy->comline->right;
	(*historic)->copy->comline->left = ptmp;
	(*historic)->copy->comline->right = tmp;
	if (tmp)
		tmp->left = (*historic)->copy->comline;
	tputs(tgetstr("im", NULL), 1, aff_c);
	aff_c((*historic)->copy->comline->c);
	tputs(tgetstr("ei", NULL), 1, aff_c);
	(*historic)->copy->size++;
	edit_line(historic);
	update_linecol(historic);
	print_comline(historic);
	if (check_ending((*historic)->copy->comline))
	{
		tputs(tgetstr("cr", NULL), 1, aff_c);
		tputs(tgetstr("do", NULL), 1, aff_c);
	}
}
