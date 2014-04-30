/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midoubih <midoubih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 15:59:40 by midoubih          #+#    #+#             */
/*   Updated: 2014/03/27 15:59:43 by midoubih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **tab, int size)
{
	int		i;
	char	**new;

	i = -1;
	if ((new = (char **)malloc(sizeof(char *) * (size + 1))) == NULL)
		return (NULL);
	while (tab[++i] && i < size)
		new[i] = ft_strdup(tab[i]);
	while (++i < size)
		new[i][0] = '\0';
	new[size] = NULL;
	return (new);
}
