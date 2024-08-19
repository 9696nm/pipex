# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 17:17:12 by hmori             #+#    #+#              #
#    Updated: 2024/08/19 16:29:20 by hana/hmori       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES = pipex.c array_units.c read_heredoc.c 
LIBFTA = libft/libft.a

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

NAME = pipex
all: $(NAME)

$(NAME): $(OBJS) $(LIBFTA)
	@cp $(LIBFTA) $@
	@ar rcs $@ $(OBJS)

$(LIBFTA):
	@make -C libft/ bonus

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

bonus: all

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

.DEFAULT_GOAL := all

.PHONY: all clean fclean bonus re $(LIBFTA)
