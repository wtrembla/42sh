/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midoubih <midoubih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 17:37:03 by midoubih          #+#    #+#             */
/*   Updated: 2014/03/27 17:41:06 by midoubih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		set_term(int set)
{
	struct termios	term;

	if (set == 1)
	{
		tcgetattr(0, &term);
		term.c_lflag &= ~(ICANON | ECHO);
		term.c_cc[VMIN] = 1;
		term.c_cc[VTIME] = 0;
		tcsetattr(0, 0, &term);
	}
	else if (set == -1)
	{
		tcgetattr(0, &term);
		term.c_lflag |= (ICANON | ECHO);
		tcsetattr(0, 0, &term);
	}
}
