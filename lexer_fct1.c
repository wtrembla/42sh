/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fct1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/25 18:16:51 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:24:41 by lfouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*new_word(char *type, char *word, int priority)
{
	t_token		*elem;

	elem = (t_token *)malloc(sizeof(t_token));
	elem->type = ft_strdup(type);
	elem->word = ft_strdup(word);
	elem->priority = priority;
	elem->next = NULL;
	return (elem);
}

static void		add_token(t_token **comlist, char *type, char *word, int i)
{
	t_token	*tmp;

	tmp = *comlist;
	if (tmp)
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_word(type, word, i);
	}
	else
		*comlist = new_word(type, word, i);
}

static char		*reorganize_comline(char *comline, int i, int j)
{
	char	*new_line;
	int		k;

	k = 0;
	new_line = (char *)malloc(sizeof(char)
									* (ft_strlen(comline) - (j - i) + 1));
	while (k < i)
	{
		new_line[k] = comline[k];
		k++;
	}
	while (comline[j])
	{
		new_line[k] = comline[j];
		j++;
		k++;
	}
	new_line[k] = '\0';
	return (new_line);
}

char			*tokenize_redi(t_token **comlist, char *comline)
{
	t_ope	operand;
	char	*word;
	int		i;
	int		j;

	i = 0;
	while (comline[i] && !(operand = check_operands(comline + i)).name)
		i++;
	j = i;
	j++;
	while (comline[j] == ' ' && comline[j])
		j++;
	while (comline[j] != ' ' && comline[j])
		j++;
	word = ft_strsub(comline, i + ft_strlen(operand.name),
			j - (i + ft_strlen(operand.name) - 1));
	add_token(comlist, "com", word, -1);
	ft_strdel(&word);
	add_token(comlist, operand.name, NULL, operand.priority);
	comline = reorganize_comline(comline, i, j);
	return (comline);
}

void			tokenize_comline(t_token **comlist, char *comline)
{
	t_ope	operand;
	char	*word;
	int		i;

	i = 0;
	while (comline[i] && !(operand = check_operands(comline + i)).name)
		i++;
	word = ft_strndup(comline, i - 1);
	if (word)
	{
		add_token(comlist, "com", word, -1);
		if (operand.name)
			add_token(comlist, operand.name, NULL, operand.priority);
		ft_strdel(&word);
		if (comline[i])
		{
			if ((comline + i + ft_strlen(operand.name)))
				read_comline(comlist, comline + i + ft_strlen(operand.name));
		}
	}
}
