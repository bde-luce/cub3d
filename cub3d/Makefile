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

# Directories
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc
LIBFT_DIR = $(SRC_DIR)/libft
MLX_DIR = mlx_linux

# Automatically find all .c files recursively
SRC = $(shell find $(SRC_DIR) -name '*.c')

# Convert src/.../*.c → obj/.../*.o
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a
MLX_LIB = $(MLX_DIR)/libmlx_Linux.a
MLX_FLAGS = -L$(MLX_DIR) -lmlx_Linux -lXext -lX11 -lm -lz

# Compiler
CC = @cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR) -I/usr/include

# Pretty messages
MSG_BUILD   = @echo "🔨 Building $(NAME)..."
MSG_DONE	= @echo "✅ Done"
MSG_CLEAN   = @echo "🧹 Cleaning objects..."
MSG_FCLEAN  = @echo "🧼 Full clean..."
MSG_RE	  = @echo "🔁 Rebuilding..."

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(MSG_BUILD)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS)
	$(MSG_DONE)

$(LIBFT):
	@echo "📚 Building libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo "🧱 Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	$(MSG_CLEAN)
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR)
	$(MSG_DONE)

fclean: clean
	$(MSG_FCLEAN)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -rf $(NAME)
	$(MSG_DONE)

re:
	$(MSG_RE)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	@rm -rf $(OBJ_DIR) $(NAME)
	@$(MAKE) -s all

.PHONY: all clean fclean re
