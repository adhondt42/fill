# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avallois <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/16 11:33:09 by avallois          #+#    #+#              #
#    Updated: 2018/01/10 16:43:43 by avallois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit

LIB = libft/libft.a

SRC = srcs/general_tools.c srcs/get_ready.c srcs/solve.c srcs/solve_1.c \
	  srcs/solve_2.c srcs/solve_3.c srcs/verify_tetri.c

all : $(NAME)

$(NAME) :
	make -C libft all
	gcc -Wall -Wextra -Werror $(SRC) $(LIB) -o $(NAME)

clean :
	make -C libft clean

fclean : clean
	make -C libft fclean
	rm -f $(NAME)

re : fclean all
