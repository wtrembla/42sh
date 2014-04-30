#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wtrembla <wtrembla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/01/21 16:26:00 by wtrembla          #+#    #+#              #
#    Updated: 2014/03/22 19:23:50 by wtrembla         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

CC			=	gcc
NAME		=	42sh

SRCS		=	aff_c.c					\
				and_fct.c				\
				arrow_fct1.c			\
				arrow_fct2.c			\
				built_cd.c				\
				built_echo.c			\
				built_env.c				\
				built_exit.c			\
				built_set_unset.c		\
				comline_fct.c			\
				command_fct.c			\
				copy_historic_fct.c		\
				delete_fct.c			\
				diverse_func.c			\
				edit_fct.c				\
				ft_strcpy_spec.c		\
				ft_echo.c				\
				get_next_line.c			\
				historic_fct.c			\
				lexer_fct1.c			\
				lexer_fct2.c			\
				main.c					\
				minishell.c				\
				move_fct1.c				\
				move_fct2.c				\
				operands_fct.c			\
				or_fct.c				\
				path_fct.c				\
				pipe_fct.c				\
				process_fct.c			\
				prompt_fct.c			\
				redil_fct.c				\
				redirr_fct.c			\
				redir_fct.c				\
				return_fct.c			\
				seek_path_fct.c			\
				scolon_fct.c			\
				signal_fct.c			\
				tab_fct.c				\
				term_fct.c				\
				tree_fct.c				\

OBJS		=	$(SRCS:.c=.o)

CFLAGS		=	-Wall -Werror -Wextra -g
HFLAGS		=	-I includes -I libft/includes
LFLAGS		=	-L libft/ -lft -ltermcap
OFLAGS		=	-O3

all:		$(NAME)

%.o:		%.c
			@$(CC) $(CFLAGS) -c $^ $(HFLAGS)

$(NAME):	libft/libft.a $(OBJS)
			@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LFLAGS)
			@echo "\033[032m[build] --- $(NAME) created\033[0m"

libft/libft.a:
			@make -C libft/ fclean
			@make -C libft
			@echo "\033[032m[build] --- libft.a created\033[0m"

clean:
			@echo "\033[031m[clean]\033[0m"
			@make -C libft/ clean
			@rm -rf $(OBJS)

fclean:		clean
			@echo "\033[031m[fclean]\033[0m"
			@make -C libft/ fclean
			@rm -rf $(NAME)

re:			fclean all

.PHONY:		all clean re fclean
