/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diverse_func.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midoubih <midoubih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 08:21:41 by midoubih          #+#    #+#             */
/*   Updated: 2014/03/27 08:21:54 by midoubih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*seek_env(char *path)
{
	t_env	*env;
	int		size_path;
	int		i;

	env = init_env(NULL);
	if (!ft_strncmp(path, "PATH", 4))
		return (env->home);
	size_path = ft_strlen(path);
	i = 0;
	while (env->environ[i])
	{
		if (!ft_strncmp(env->environ[i], path, size_path))
			return (env->environ[i]);
		++i;
	}
	return (NULL);
}

int				ft_strlen_to_char(char *str, char c)
{
	int		size;

	size = 0;
	while (str[size] && str[size] != c)
		++size;
	return (size);
}

char			*ft_strdup_to_char(char *str, char c)
{
	int		i;
	int		size;
	char	*ret;

	i = 0;
	size = ft_strlen_to_char(str, c);
	ret = (char *)malloc(size + 1);
	while (i < size)
	{
		ret[i] = str[i];
		++i;
	}
	ret[i] = '\0';
	return (ret);
}
