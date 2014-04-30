/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 15:56:55 by midoubih          #+#    #+#             */
/*   Updated: 2014/03/27 23:22:17 by lfouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		exit_fct(char *msg)
{
	t_env		*env;

	(void)msg;
	env = init_env(NULL);
	if (env)
	{
		if (env->environ)
			del_tab(env->environ);
		if (env->path)
			del_tab(env->path);
		free(env);
		env = NULL;
		del_operands(init_operands());
		del_keytab();
		del_proctab();
		set_term(-1);
	}
	exit(0);
}
