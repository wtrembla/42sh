/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lfouquet <lfouquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/02/26 18:20:04 by wtrembla          #+#    #+#             */
/*   Updated: 2014/03/27 23:29:18 by lfouquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*
** include
*/
# include <fcntl.h>
# include "get_next_line.h"
# include <sys/ioctl.h>
# include "../libft/includes/libft.h"
# include <termcap.h>
# include <termios.h>

/*
** define
*/
# define KEY_NUM	13
# define OPE_NUM	7

/*
** typedef
*/
typedef struct			s_env
{
	char				**environ;
	char				**path;
	char				*home;
}						t_env;

typedef struct			s_ope
{
	int					priority;
	char				*name;
}						t_ope;

typedef struct			s_token
{
	char				*type;
	char				*word;
	int					priority;
	struct s_token		*next;
}						t_token;

typedef struct			s_node
{
	char				*type;
	char				*word;
	int					pos;
	struct s_node		*left;
	struct s_node		*right;
}						t_node;

typedef struct			s_comline
{
	char				c;
	int					col;
	struct s_comline	*right;
	struct s_comline	*left;
}						t_comline;

typedef struct			s_copy
{
	char				*line;
	int					size;
	struct s_copy		*up;
	struct s_copy		*down;
	t_comline			*comline;
}						t_copy;

typedef struct			s_historic
{
	char				**historic;
	int					prompt;
	t_copy				*copy;
}						t_historic;

typedef void			(*t_keyptr)(t_historic **);

typedef struct			s_key
{
	char				*keyword;
	t_keyptr			apply_key;
}						t_key;

typedef void			(*t_procptr)(t_node *, int, int);

typedef struct			s_proc
{
	char				*operand;
	t_procptr			apply_proc;
}						t_proc;

typedef struct			s_id
{
	int					id;
	pid_t				child;
	pid_t				father;
	int					built;
}						t_id;

/*
** aff_c.c
*/
int						aff_c(int c);
int						aff_str(char *str);

/*
** and_fct.c
*/
void					and_proc(t_node *tree, int fd_in, int fd_out);

/*
** arrow_fct1.c
*/
void					apply_arrowleft(t_historic **historic);
void					apply_arrowright(t_historic **historic);
int						check_beginning(t_comline *comline);
int						check_ending(t_comline *comline);

/*
** arrow_fct2.c
*/
void					apply_arrowdown(t_historic **historic);
void					apply_arrowup(t_historic **historic);
void					clear_aff(t_historic **historic);
void					display_comline(t_historic **historic);

/*
** built_cd.c
*/
int						cd_fct(char *msg);

/*
** built_echo.c
*/
int						echo_fct(char *msg);

/*
** built_env.c
*/
void					env_fct(char *msg);

/*
** built_exit.c
*/
void					exit_fct(char *msg);

/*
** built_set_unset.c
*/
int						setenv_fct(char *var);
int						unsetenv_fct(char *var);

/*
** comline_fct.c
*/
t_comline				*add_char_to_comline(char c);
void					del_comline(t_comline *comline);

/*
** command_fct.c
*/
char					*check_command(char *command);
int						command_proc(char *command, int fd_in, int fd_out);

/*
** copy_historic_fct.c
*/
t_copy					*copy_historic(char **historic, int prompt);
void					del_copy(t_copy *copy);

/*
** delete_fct.c
*/
void					apply_delete(t_historic **historic);
void					print_comline(t_historic **historic);
void					update_linecol(t_historic **historic);

/*
** diverse_func.c
*/
char					*seek_env(char *path);
int						ft_strlen_to_char(char *str, char c);
char					*ft_strdup_to_char(char *str, char c);

/*
** edit_fct.c
*/
void					apply_edit(t_historic **historic, char c);
void					edit_line(t_historic **historic);

/*
** ft_strcpy_spec.c
*/
char					*ft_strcpy_spec(char *s1, const char *s2);

/*
** historic_fct.c
*/
char					**add_to_historic(char **historic, char *comline);
t_historic				*init_historic(int prompt);

/*
** lexer_fct1.c
*/
void					tokenize_comline(t_token **comlist, char *comline);
char					*tokenize_redi(t_token **comlist, char *comline);

/*
** lexer_fct2.c
*/
void					del_comlist(t_token *comlist);
void					organize_com(t_node **tree, t_token **comlist, int pos,
							int i);
void					read_comline(t_token **comlist, char *comline);

/*
** main.c
*/
t_env					*init_env(char **environ);

/*
** minishell.c
*/
void					del_keytab(void);
void					minishell(t_historic **historic);

/*
** move_fct1.c
*/
void					apply_movedown(t_historic **historic);
void					apply_movenext(t_historic **historic);
void					apply_moveprev(t_historic **historic);
void					apply_moveup(t_historic **historic);

/*
** move_fct2.c
*/
void					apply_movebegin(t_historic **historic);
void					apply_moveend(t_historic **historic);

/*
** or_fct.c
*/
void					or_proc(t_node *tree, int fd_in, int fd_out);

/*
** operands_fct.c
*/
t_ope					check_operands(char *comline);
void					del_operands(t_ope *operands);
t_ope					*init_operands(void);

/*
** path_fct.c
*/
char					*build_path(char *path, char *command);
int						check_path(char *path);
void					improper_path(int ret, char *path);

/*
** pipe_fct.c
*/
void					pipe_proc(t_node *tree, int fd_in, int fd_out);

/*
** process_fct.c
*/
void					read_tree(t_node *tree, int fd_in, int fd_out);
void					del_proctab(void);

/*
** prompt_fct.c
*/
int						display_prompt(char **environ);

/*
** redil_fct.c
*/
int						remove_file_redil(void);
int						get_fd_file_redil(int status);
void					redil_proc(t_node *tree, int fd_in, int fd_out);

/*
** redir_fct.c
*/
void					redir_proc(t_node *tree, int fd_in, int fd_out);

/*
** redirr_fct.c
*/
void					redirr_proc(t_node *tree, int fd_in, int fd_out);

/*
** return_fct.c
*/
void					apply_return(t_historic **historic);

/*
** seek_path_fct.c
*/
char					*seek_true_path(char *actual_dir, char *path);

/*
** scolon_fct.c
*/
void					scolon_proc(t_node *tree, int fd_in, int fd_out);

/*
** tab_fct.c
*/
int						ft_tablen(char **tab);
void					del_tab(char **tab);

/*
** term_fct.c
*/
void					set_term(int set);

/*
** tree_fct.c
*/
void					add_node(t_node **tree, t_node *elem);
void					clear_tree(t_node **tree);
t_node					*new_node(char *type, char *word, int pos);
void					ft_print_tree(t_node *tree);

/*
** seek_env_fct.c
*/
void					ft_signal(void);

#endif
