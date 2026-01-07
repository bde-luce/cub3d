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

SRC_DIR = src
SRCS = parsing.c
SRC  = $(addprefix $(SRC_DIR)/, $(SRCS))

OBJ_DIR = obj
OBJS = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

CC = @cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

INC_DIR = inc
LIBFT_DIR = $(SRC_DIR)/libft
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR) -I/usr/include

RM = @rm -rf

# Pretty messages (1 line)
MSG_BUILD   = @echo "🔨 Building $(NAME)..."
MSG_DONE    = @echo "✅ Done"
MSG_CLEAN   = @echo "🧹 Cleaning objects..."
MSG_FCLEAN  = @echo "🧼 Full clean..."
MSG_RE      = @echo "🔁 Rebuilding..."


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(MSG_BUILD)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFT)
	$(MSG_DONE)

$(LIBFT):
	@echo "📚 Building libft..."
	@$(MAKE) -s -C $(LIBFT_DIR)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "🧱 Compiling $<"
	$(CC) $(CFLAGS) $(INCLUDES) -c -o $@ $<

clean:
	$(MSG_CLEAN)
	@$(MAKE) -s clean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR)
	$(MSG_DONE)

fclean: clean
	$(MSG_FCLEAN)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	$(RM) $(NAME)
	$(MSG_DONE)

re:
	$(MSG_RE)
	@$(MAKE) -s fclean -C $(LIBFT_DIR)
	$(RM) $(OBJ_DIR) $(NAME)
	@$(MAKE) -s all

.PHONY: all clean fclean re