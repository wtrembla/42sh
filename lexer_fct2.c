/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fct2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/22 17:05:26 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:31:34 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			read_comline(t_token **comlist, char *comline)
{
	t_ope	operand;
	char	*tmp1;
	char	*tmp2;
	int		i;

	i = 0;
	while (comline[i] && !(operand = check_operands(comline + i)).name)
		i++;
	if (comline[i] && (!ft_strcmp(operand.name, ">")
						|| !ft_strcmp(operand.name, "<")
						|| !ft_strcmp(operand.name, ">>")))
	{
		tmp1 = ft_strdup(comline);
		tmp2 = tokenize_redi(comlist, tmp1);
		ft_strdel(&tmp1);
		read_comline(comlist, tmp2);
		ft_strdel(&tmp2);
	}
	else
		tokenize_comline(comlist, comline);
}

static t_ope	new_ope(void)
{
	t_ope	op;

	op.name = NULL;
	op.priority = -1;
	return (op);
}

void			organize_com(t_node **tree, t_token **comlist, int pos, int p)
{
	t_ope		op;
	t_token		*tmp;

	tmp = *comlist;
	op = new_ope();
	while (tmp && tmp->next && tmp->next->type)
	{
		op = check_operands(tmp->type);
		if (op.name != NULL && op.priority == p)
			break ;
		else
			tmp = tmp->next;
	}
	if (op.name && !ft_strcmp(op.name, tmp->type) && (op.priority == p))
	{
		add_node(tree, new_node(tmp->type, tmp->word, pos));
		ft_strdel(&tmp->type);
		organize_com(tree, comlist, pos * 2, op.priority);
		organize_com(tree, &tmp->next, pos * 2 + 1, op.priority);
	}
	else if (p < 4)
		organize_com(tree, comlist, pos, p + 1);
	else if (tmp && !ft_strcmp(tmp->type, "com"))
		add_node(tree, new_node("com", tmp->word, pos));
}

void			del_comlist(t_token *comlist)
{
	t_token		*ptmp;

	if (comlist)
	{
		while (comlist)
		{
			ptmp = comlist;
			comlist = comlist->next;
			ft_strdel(&ptmp->type);
			ft_strdel(&ptmp->word);
			free(ptmp);
			ptmp->next = NULL;
			ptmp = NULL;
		}
	}
}
