# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jajuntti <jajuntti@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/31 15:00:04 by jajuntti          #+#    #+#              #
#    Updated: 2024/04/23 14:33:58 by jajuntti         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

SRC_DIR = src/
SRC = philo.c \
	data.c \
	get_int.c \
	threads.c \
	time.c \
	utils.c
SRCS = $(addprefix $(SRC_DIR), $(SRC))

INC_DIR = inc/
INC = philo.h
INCS = $(addprefix $(INC_DIR), $(INC))

OBJ_DIR = obj/
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME)
	
$(NAME): $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(INC_DIR)

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INCS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re