# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/20 16:14:06 by zabdulza          #+#    #+#              #
#    Updated: 2023/12/20 16:15:34 by zabdulza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX = minilibx-linux
	EVENT = src/event_linux.c
	MLX_LIB = $(MLX)/libmlx.a
	FLAGS = -lXext -lX11 ./$(MLX)/libmlx.a -I./$(MLX) -L./$(MLX) -lmlx
endif

NAME = so_long
CC = cc
SRC = $(wildcard src/*.c)
OBJ = $(SRC:%.c=%.o)
CFLAGS = -Wall -Wextra -Werror

.PHONY:		all clean fclean test re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(MLX)
	@$(CC) -o $@ $? $(MLX_LIB) $(FLAGS) $(CFLAGS)
	@echo Game is ready...
	@echo GAME_START:    ./so_long maps/map.ber
	@echo OR:  make test
	@echo Controls: W A S D
	
$(OBJ): $(SRC)
	@$(CC) $(CFLAGS) -c $?
	@mv *.o src

clean:
	@rm -rf src/*.o
	@make clean -C $(MLX)

fclean: clean
	@rm -rf $(NAME)

re: fclean all
	@rm -rf src/*.o

test: all
	./so_long maps/map.ber
