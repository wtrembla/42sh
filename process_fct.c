/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_fct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/03/12 17:35:37 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:31:52 by sboeuf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_proc	init_process(char *operand, t_procptr apply_proc)
{
	t_proc		process;

	process.operand = ft_strdup(operand);
	process.apply_proc = apply_proc;
	return (process);
}

static t_proc	*init_proctab(void)
{
	static t_proc	*proc_tab = NULL;

	if (!proc_tab)
	{
		if (!(proc_tab = (t_proc *)malloc(sizeof(t_proc) * OPE_NUM)))
			ft_error("init_proctab: memory allocation failed");
		proc_tab[0] = init_process(";", &scolon_proc);
		proc_tab[1] = init_process("&&", &and_proc);
		proc_tab[2] = init_process("||", &or_proc);
		proc_tab[3] = init_process("|", &pipe_proc);
		proc_tab[4] = init_process("<", &redil_proc);
		proc_tab[5] = init_process(">>", &redirr_proc);
		proc_tab[6] = init_process(">", &redir_proc);
	}
	return (proc_tab);
}

static int		check_built(char *buff)
{
	int		ret;

	ret = 1;
	if (!(ret = ft_strcmp(buff, "exit")))
		exit_fct(NULL);
	else if (!(ret = ft_strcmp(buff, "env")))
		env_fct(NULL);
	else if (!(ret = ft_strncmp(buff, "echo ", 5)) || !ft_strcmp(buff, "echo"))
		echo_fct(buff + 4);
	else if (!(ret = ft_strncmp(buff, "cd ", 3)) || !ft_strcmp(buff, "cd"))
		cd_fct(buff + 3);
	else if (!(ret = ft_strncmp(buff, "setenv", 6)))
		setenv_fct(buff + 6);
	else if (!(ret = ft_strncmp(buff, "unsetenv", 8)))
		unsetenv_fct(buff + 8);
	return (ret);
}

void			del_proctab(void)
{
	int			i;
	t_proc		*proc_tab;

	proc_tab = init_proctab();
	if (proc_tab)
	{
		i = 0;
		while (i < OPE_NUM)
		{
			free(proc_tab[i].operand);
			proc_tab[i].operand = NULL;
			++i;
		}
	}
}

void			read_tree(t_node *tree, int fd_in, int fd_out)
{
	int			i;
	t_proc		*proc_tab;

	i = 0;
	proc_tab = init_proctab();
	if (tree)
	{
		while (i < OPE_NUM)
		{
			if (!ft_strcmp(tree->type, proc_tab[i].operand))
			{
				proc_tab[i].apply_proc(tree, fd_in, fd_out);
				break ;
			}
			i++;
		}
		if (!ft_strcmp(tree->type, "com"))
		{
			if (check_built(tree->word))
			{
				command_proc(tree->word, fd_in, fd_out);
				set_term(1);
			}
		}
	}
}
