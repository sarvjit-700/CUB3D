# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ssukhija <ssukhija@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/07 14:45:50 by ssukhija          #+#    #+#              #
#    Updated: 2025/08/07 14:45:50 by ssukhija         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:

# colours
RESET = \033[0m
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m

NAME = cub3d

# flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -O3
MLX_FLAGS = -lglfw -ldl -lGL -lm -pthread
RM = rm -rf

# paths
LIBFT_DIR	:= ./libft
LIBFT	:= $(LIBFT_DIR)/libft.a
PARSING	:= ./src/parsing
RENDER	:= ./src/rendering

MLX_DIR = MLX42
MLX_LIB = $(MLX_DIR)/build/libmlx42.a
MLX_INC = -I$(MLX_DIR)/include



# files
SRC = $(PARSING)/main.c $(PARSING)/map_help.c $(PARSING)/validate_grid.c\
		$(PARSING)/colours.c $(PARSING)/error_handling.c $(PARSING)/utils.c\
		$(PARSING)/parse_flags.c $(RENDER)/draw.c $(RENDER)/player.c $(RENDER)/textures.c $(RENDER)/dda.c

OBJ = $(SRC:.c=.o)

INCLUDES = -Iincludes -I$(LIBFT_DIR) -I MLX42/include


# rules
all: $(LIBFT) $(MLX_LIB) $(NAME)


src/%.o : src/%.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(INCLUDES) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(MLX_LIB) $(MLX_FLAGS) -o $(NAME)
	printf "Linking executable	$(GREEN)[OK]$(RESET)\n"

$(LIBFT):
	printf "Making Libft		$(YELLOW)[OK]$(RESET)\n"
	$(MAKE) -sC $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	printf "clean object files	$(YELLOW)[OK]$(RESET)\n"
	$(MAKE) fclean -sC $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	printf "cleaning all files	$(YELLOW)[OK]$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re