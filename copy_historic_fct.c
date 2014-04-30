/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_historic_fct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 21:07:56 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 22:28:25 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_comline	*copy_comline(t_comline *copy, char *comline, int prompt)
{
	int			i;
	t_comline	*elem;
	t_comline	*tmp;

	i = 0;
	if (comline)
	{
		while (comline[i])
		{
			tmp = copy;
			elem = add_char_to_comline(comline[i]);
			elem->col = prompt + i;
			if (tmp)
			{
				while (tmp->right)
					tmp = tmp->right;
				tmp->right = elem;
				tmp->right->left = tmp;
			}
			else
				copy = elem;
			i++;
		}
	}
	return (copy);
}

static t_copy		*add_to_copy(t_copy *copy, char *comline, int prompt)
{
	t_copy	*elem;
	t_copy	*tmp;

	tmp = copy;
	if (!(elem = (t_copy *)malloc(sizeof(t_copy))))
		ft_error("add_to_copy: memory allocation failed");
	elem->line = ft_strdup(comline);
	elem->size = ft_strlen(comline);
	elem->up = NULL;
	elem->down = NULL;
	elem->comline = add_char_to_comline('\0');
	elem->comline->col = prompt - 1;
	elem->comline = copy_comline(elem->comline, comline, prompt);
	if (tmp)
	{
		while (tmp->down)
			tmp = tmp->down;
		tmp->down = elem;
		tmp->down->up = tmp;
	}
	else
		copy = elem;
	return (copy);
}

t_copy				*copy_historic(char **historic, int prompt)
{
	int			i;
	t_copy		*copy;

	i = 0;
	copy = NULL;
	while (historic && historic[i])
	{
		copy = add_to_copy(copy, historic[i], prompt);
		i++;
	}
	copy = add_to_copy(copy, NULL, prompt);
	while (copy->down)
	{
		if (copy->size)
			copy->comline = copy->comline->right;
		copy = copy->down;
	}
	return (copy);
}

void				del_copy(t_copy *copy)
{
	t_copy	*tmp;

	while (copy->up)
		copy = copy->up;
	while (copy)
	{
		tmp = copy;
		copy = copy->down;
		ft_strdel(&tmp->line);
		del_comline(tmp->comline);
		tmp->up = NULL;
		tmp->down = NULL;
		free(tmp);
		tmp = NULL;
	}
}
