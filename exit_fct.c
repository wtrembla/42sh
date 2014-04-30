/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midoubih <midoubih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/24 18:01:23 by midoubih          #+#    #+#             */
/*   Updated: 2014/03/24 18:21:05 by midoubih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_tab(char **tab)
{
	int		i;

	if (tab)
	{
		i = 0;
		while (tab[i])
		{
			free(tab[i]);
			tab[i] = NULL;
			i++;
		}
		free(tab);
	}
}

void		exit_fct(char *msg)
{
	t_env		*env;

	env = init_env(NULL);
	del_tab(env->environ);
	del_tab(env->path);
	free(env);
	env = NULL;
	del_operands(init_operands());
	del_keytab();
	del_proctab();
	msg = msg;
	exit(0);
}
