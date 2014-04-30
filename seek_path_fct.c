/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seek_path_fct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midoubih <midoubih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 08:25:34 by midoubih          #+#    #+#             */
/*   Updated: 2014/03/27 08:25:36 by midoubih         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		**suppr_last_dir(char **path_tab)
{
	char	**new_tab;
	int		size_tab;
	int		i;

	i = 0;
	size_tab = ft_tablen(path_tab);
	new_tab = (char **)malloc(sizeof(char *) * size_tab);
	while (i < size_tab - 1)
	{
		new_tab[i] = ft_strdup(path_tab[i]);
		i++;
	}
	new_tab[i] = NULL;
	del_tab(path_tab);
	return (new_tab);
}

static int		add_dir(char ***path_tab, char *path)
{
	char	**new_tab;
	int		size;

	size = ft_tablen(*path_tab);
	new_tab = ft_tabdup(*path_tab, size + 1);
	new_tab[size] = ft_strdup_to_char(path, '/');
	del_tab(*path_tab);
	*path_tab = new_tab;
	size = 0;
	while (path[size] && path[size] != '/')
		++size;
	return (size);
}

static int		tab_nb_char(char **tab)
{
	int		i;
	int		j;
	int		size;

	size = 0;
	j = 0;
	while (tab[j])
	{
		i = 0;
		++size;
		while (tab[j][i])
		{
			++size;
			++i;
		}
		++j;
	}
	return (size);
}

static char		*join_path(char **tab, int put_home)
{
	int		i;
	int		j;
	int		size;
	char	*path;

	size = tab_nb_char(tab) + (put_home * ft_strlen(seek_env("HOME")));
	path = (char *)malloc(size + 1);
	path = (put_home) ? ft_strcpy(path, seek_env("HOME")) : (path);
	size = 0;
	j = 0;
	while (tab[j])
	{
		i = 0;
		path[size] = '/';
		size++;
		while (tab[j][i])
		{
			path[size] = tab[j][i];
			++size;
			++i;
		}
		++j;
	}
	path[size] = '\0';
	return (path);
}

char			*seek_true_path(char *path, char *actual_dir)
{
	char		**tmp;

	tmp = ft_strsplit(actual_dir, '/');
	while (path && *path)
	{
		if (*path == '/' || (*path == '.' && !*(path + 1)))
			++path;
		else if (*path == '.' && *(path + 1) == '/')
			path += 2;
		else if (*path == '.' && *(path + 1) == '.')
		{
			tmp = suppr_last_dir(tmp);
			path += 3;
		}
		else
			path += add_dir(&tmp, path);
	}
	if (*actual_dir == '~')
		return (join_path(tmp, 1));
	else
		return (join_path(tmp, 0));
}
