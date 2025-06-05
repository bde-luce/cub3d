# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bde-luce <bde-luce@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 13:01:43 by bde-luce          #+#    #+#              #
#    Updated: 2025/05/13 13:01:43 by bde-luce         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

OBJ_DIR = obj

SRCS = parsing.c

OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

INCLUDES = -I/usr/include -I$(LIBFT_DIR)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
RM = rm -rf

LIBFT_DIR = ./libft
LIBFT = ./libft/libft.a


all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -C $(LIBFT_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re