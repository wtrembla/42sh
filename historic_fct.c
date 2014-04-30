/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   historic_fct.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/28 18:44:45 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 22:35:08 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		del_historic(char **historic)
{
	int		i;

	i = 0;
	if (historic)
	{
		while (historic[i])
		{
			ft_strdel(&historic[i]);
			i++;
		}
		free(historic);
		historic = NULL;
	}
}

char			**add_to_historic(char **historic, char *comline)
{
	char	**update;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (historic && historic[i])
		i++;
	if (!(update = (char **)malloc(sizeof(char *) * (i + 2))))
		ft_error("add_to_historic: memory allocation failed");
	while (historic && historic[j])
	{
		update[j] = ft_strdup(historic[j]);
		j++;
	}
	update[j++] = ft_strdup(comline);
	update[j] = NULL;
	del_historic(historic);
	return (update);
}

t_historic		*init_historic(int prompt)
{
	char		*line;
	int			fd;
	t_historic	*historic;

	if (!(historic = (t_historic *)malloc(sizeof(t_historic))))
		ft_error("init_historic: memory allocation failed");
	if ((fd = open(".42sh_historic", O_RDONLY)) == -1)
		ft_error("init_historic: open failed on file .42sh_historic");
	historic->historic = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		historic->historic = add_to_historic(historic->historic, line);
		ft_strdel(&line);
	}
	historic->prompt = prompt;
	historic->copy = copy_historic(historic->historic, prompt);
	if (close(fd) == -1)
		ft_error("init_historic: close failed on file .42sh_historic");
	return (historic);
}
