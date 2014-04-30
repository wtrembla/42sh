/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_fct2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/11 17:20:20 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/11 21:02:36 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	apply_moveend(t_historic **historic)
{
	clear_aff(historic);
	display_comline(historic);
}

void	apply_movebegin(t_historic **historic)
{
	struct winsize	size;

	ioctl(0, TIOCGWINSZ, &size);
	while ((*historic)->copy->comline->col >= size.ws_col)
		apply_moveup(historic);
	while ((*historic)->copy->comline->c != '\0')
		(*historic)->copy->comline = (*historic)->copy->comline->left;
	tputs(tgoto(tgetstr("ch", NULL), 0, (*historic)->prompt), 1, aff_c);
}
