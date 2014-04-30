/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operands_fct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 18:27:08 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:11:57 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_ope	init_ope(int priority, char *name)
{
	t_ope		ope;

	ope.priority = priority;
	ope.name = name;
	return (ope);
}

t_ope			*init_operands(void)
{
	static t_ope	*ope_tab;

	if (!ope_tab)
	{
		ope_tab = (t_ope *)malloc(sizeof(t_ope) * OPE_NUM);
		ope_tab[0] = init_ope(0, ft_strdup(";"));
		ope_tab[1] = init_ope(1, ft_strdup("&&"));
		ope_tab[2] = init_ope(1, ft_strdup("||"));
		ope_tab[3] = init_ope(2, ft_strdup("|"));
		ope_tab[4] = init_ope(3, ft_strdup(">>"));
		ope_tab[5] = init_ope(3, ft_strdup(">"));
		ope_tab[6] = init_ope(3, ft_strdup("<"));
	}
	return (ope_tab);
}

t_ope			check_operands(char *comline)
{
	t_ope	*ope_tab;
	t_ope	ope_null;
	int		i;

	i = 0;
	ope_null.name = NULL;
	ope_null.priority = -1;
	ope_tab = init_operands();
	while (i < OPE_NUM)
	{
		if (!ft_strncmp(comline, ope_tab[i].name, ft_strlen(ope_tab[i].name)))
			return (ope_tab[i]);
		i++;
	}
	return (ope_null);
}

void			del_operands(t_ope *ope_tab)
{
	int		i;

	i = 0;
	if (ope_tab)
	{
		while (i < OPE_NUM)
		{
			ft_strdel(&ope_tab[i].name);
			i++;
		}
		free(ope_tab);
		ope_tab = NULL;
	}
}
