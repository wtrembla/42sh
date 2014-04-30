/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/21 12:14:20 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:02:30 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *s1, const void *s2, size_t n)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = (char *)s1;
	tmp2 = (char *)s2;
	if (tmp1 <= tmp2 || tmp2 >= tmp1 + n)
	{
		while (n--)
			*tmp1++ = *tmp2++;
	}
	else
	{
		tmp1 = tmp1 + n - 1;
		tmp2 = tmp2 + n - 1;
		while (n--)
			*tmp1-- = *tmp2--;
	}
	return (s1);
}
