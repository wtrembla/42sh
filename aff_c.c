/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 18:12:14 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/04 16:36:36 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		aff_c(int c)
{
	int		fd;

	if ((fd = open(ttyname(0), O_WRONLY)) == -1)
		ft_error("aff_c: error opening new interface");
	write(fd, &c, 1);
	if (close(fd) == -1)
		ft_error("aff_c: error closing new interface");
	return (0);
}

int		aff_str(char *str)
{
	int		fd;

	if ((fd = open(ttyname(0), O_WRONLY)) == -1)
		ft_error("aff_str: error opening new interface");
	ft_putstr_fd(str, fd);
	if (close(fd) == -1)
		ft_error("aff_str: error closing new interface");
	return (0);
}
