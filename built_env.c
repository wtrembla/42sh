/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midoubih <midoubih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/25 17:02:35 by midoubih          #+#    #+#             */
/*   Updated: 2014/03/27 21:46:34 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			env_fct(char *msg)
{
	t_env		*env;
	char		**ptr;

	(void)msg;
	env = init_env(NULL);
	if (env && env->environ)
	{
		ptr = env->environ;
		while (*ptr)
			ft_putendl(*ptr++);
		ptr = NULL;
	}
}
