# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 17:17:12 by hmori             #+#    #+#              #
#    Updated: 2024/08/24 22:46:25 by hana/hmori       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES = pipex.c pipe_units.c read_heredoc.c other_units.c

LIBFT = libft
LIBFTA = $(LIBFT)/libft.a

SRC_DIR = src
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = obj
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

NAME = pipex

all: $(LIBFT) $(NAME)

$(NAME): $(OBJS) $(LIBFTA)
	@$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft/ bonus

bonus: all

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

.DEFAULT_GOAL := all

.PHONY: all clean fclean bonus re $(LIBFT)

# CC = cc
# CFLAGS = -Wall -Wextra -Werror

# SRC_FILES = pipex.c pipe_units.c read_heredoc.c other_units.c
# LIBFTA = libft/libft.a

# SRC_DIR = src
# SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# NAME = pipex

# all: $(NAME)

# $(NAME): $(SRCS) $(LIBFTA)
# 	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFTA)

# $(LIBFTA):
# 	@make -C libft/ bonus

# bonus: all

# clean:
# 	@make -C libft/ clean

# fclean: clean
# 	@make -C libft/ fclean
# 	@rm -f $(NAME)

# re: fclean all

# .DEFAULT_GOAL := all

# .PHONY: all clean fclean bonus re $(LIBFTA)
