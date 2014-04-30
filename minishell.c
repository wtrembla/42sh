/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 20:52:39 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:11:07 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			handle_sig(int s)
{
	if (s == SIGINT)
	{
		set_term(-1);
		exit(0);
	}
}

static t_key	init_key(char *keyword, t_keyptr apply_key)
{
	t_key		key;

	key.keyword = ft_strdup(keyword);
	key.apply_key = apply_key;
	return (key);
}

static t_key	*init_keytab(void)
{
	static t_key	*key_tab = NULL;

	if (!key_tab)
	{
		if (!(key_tab = (t_key *)malloc(sizeof(t_key) * KEY_NUM)))
			ft_error("init_keytab: memory allocation failed");
		key_tab[0] = init_key("\012", &apply_return);
		key_tab[1] = init_key("\033[A", &apply_arrowup);
		key_tab[2] = init_key("\033[B", &apply_arrowdown);
		key_tab[3] = init_key("\033[D", &apply_arrowleft);
		key_tab[4] = init_key("\033[C", &apply_arrowright);
		key_tab[5] = init_key("\177", &apply_delete);
		key_tab[6] = init_key("\033[3~", &apply_delete);
		key_tab[7] = init_key("\033\033[A", &apply_moveup);
		key_tab[8] = init_key("\033\033[B", &apply_movedown);
		key_tab[9] = init_key("\033\033[D", &apply_moveprev);
		key_tab[10] = init_key("\033\033[C", &apply_movenext);
		key_tab[11] = init_key("\033[H", &apply_movebegin);
		key_tab[12] = init_key("\033[F", &apply_moveend);
	}
	return (key_tab);
}

void			del_keytab(void)
{
	int		i;
	t_key	*key_tab;

	i = 0;
	key_tab = init_keytab();
	if (key_tab)
	{
		while (i < KEY_NUM)
		{
			ft_strdel(&(key_tab[i].keyword));
			i++;
		}
		free(key_tab);
		key_tab = NULL;
	}
}

void			minishell(t_historic **historic)
{
	char		*buf;
	int			i;
	t_key		*key_tab;

	ft_signal();
	buf = ft_strnew(7);
	i = 0;
	key_tab = init_keytab();
	while (read(0, buf, 6))
	{
		while (i < KEY_NUM)
		{
			if (!ft_strcmp(buf, key_tab[i].keyword))
			{
				key_tab[i].apply_key(historic);
				break ;
			}
			i++;
		}
		if (ft_isprint(buf[0]))
			apply_edit(historic, buf[0]);
		i = 0;
		ft_bzero(buf, ft_strlen(buf));
	}
}
