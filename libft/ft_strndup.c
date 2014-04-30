/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/03 15:40:07 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 22:08:59 by lfouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, int n)
{
	int		i;
	char	*ndup;

	i = 0;
	if (n < 0)
		return (NULL);
	if (!(ndup = (char *)malloc(sizeof(char) * (n + 2))))
		return (NULL);
	while (i <= n)
	{
		ndup[i] = str[i];
		i++;
	}
	ndup[i] = '\0';
	return (ndup);
}
