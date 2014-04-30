/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_fct.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 20:26:38 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 21:59:18 by lfouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*build_path(char *path, char *command)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(path, "/");
	tmp2 = ft_strjoin(tmp1, command);
	ft_strdel(&tmp1);
	return (tmp2);
}

int		check_path(char *path)
{
	if (access(path, F_OK) == -1)
		return (-1);
	if (access(path, X_OK) == -1)
		return (-2);
	return (0);
}

void	improper_path(int ret, char *path)
{
	if (ret == -1)
		ft_putjoin("42sh: command not found ", path);
	else if (ret == -2)
		ft_putjoin("42sh: execute/search permission denied ", path);
}
