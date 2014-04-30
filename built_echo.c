/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_echo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: midoubih <midoubih@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/27 09:40:57 by midoubih          #+#    #+#             */
/*   Updated: 2014/03/27 21:46:08 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*print_unprintable_char(char c, char *str, int opt_n)
{
	++str;
	while (*str && *str != c)
	{
		if (*str == '\\' && *(str + 1) == 't')
			ft_putchar('\t');
		else if (*str == '\\' && *(str + 1) == 'v')
			ft_putchar('\v');
		else if (*str == '\\' && *(str + 1) == 'n' && !opt_n)
			ft_putchar('\n');
		else if (*str == '\\' && *(str + 1) == 'e')
			ft_putchar('\e');
		else if (*str == '\\' && *(str + 1) == 'b')
			ft_putchar('\b');
		else if (*str == '\\' && *(str + 1) == 'f')
			ft_putchar('\f');
		else if (*str == '\\')
		{
			ft_putchar(*(++str));
			str -= 2;
		}
		else
			ft_putchar(*str--);
		str += 2;
	}
	return (--str);
}

static int	print_str(char *str, int opt_n)
{
	char	*ptr;

	ptr = str;
	while (*ptr)
	{
		if (*ptr == '\"' || *ptr == '\'')
			ptr = print_unprintable_char(*ptr, ptr, opt_n);
		else if (*ptr == '\\')
			ft_putchar(*(++ptr));
		else
			ft_putchar(*ptr);
		++ptr;
	}
	if (*ptr && *ptr == '\\' && *(ptr + 1) == 'c')
		return (0);
	return (1);
}

int			echo_fct(char *msg)
{
	char	**ptr;
	int		opt_n;

	opt_n = 0;
	if (*msg)
	{
		ptr = ft_strsplit(msg, ' ');
		if (*ptr && !ft_strcmp(ptr[0], "-n"))
		{
			++opt_n;
			++ptr;
		}
		while (*ptr)
		{
			if (!(print_str(*ptr, opt_n)))
			{
				opt_n = 1;
				break ;
			}
			ft_putchar(' ');
			++ptr;
		}
	}
	if (!opt_n)
		ft_putchar('\n');
	return (1);
}
