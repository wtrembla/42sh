/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2013/11/19 18:28:57 by wtrembla          #+#    #+#             */
/*   Updated: 2013/12/22 16:04:53 by wtrembla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	int		i;
	char	*scpy;

	if (!s1)
		return (NULL);
	i = 0;
	scpy = NULL;
	scpy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (scpy == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		scpy[i] = s1[i];
		i++;
	}
	scpy[i] = '\0';
	return (scpy);
}
