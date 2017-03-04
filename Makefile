# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chansen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/03 18:41:46 by chansen           #+#    #+#              #
#    Updated: 2017/03/03 18:41:47 by chansen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fractol

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c \

LFT = -I libft -L libft -lft

MLX = -I minilibx -L minilibx -lmlx

FRAME = -framework OpenGL -framework WorkLS

RM = rm -rf

all: $(NAME)

$(NAME):
	make -C ./libft/ re
	make -C ./minilibx/ re
	$(CC) $(CFLAGS) $(LFT) $(MLX) $(FRAME) $(SRC) -o $(NAME)

clean:
	make -C ./libft/ clean

fclean:
	make -C ./minilibx/ clean
	make -C ./libft/ fclean
	$(RM) $(NAME)
