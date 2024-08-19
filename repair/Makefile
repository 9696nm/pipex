# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hana/hmori <sagiri.mori@gmail.com>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/19 17:17:12 by hmori             #+#    #+#              #
#    Updated: 2024/08/19 22:35:57 by hana/hmori       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_FILES = pipex.c pipe_units.c read_heredoc.c other_units.c
LIBFTA = libft/libft.a

SRC_DIR = src
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))

NAME = pipex

all: $(NAME)

$(NAME): $(SRCS) $(LIBFTA)
	@$(CC) $(CFLAGS) -o $(NAME) $(SRCS) $(LIBFTA)

$(LIBFTA):
	@make -C libft/ bonus

bonus: all

clean:
	@make -C libft/ clean

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)

re: fclean all

.DEFAULT_GOAL := all

.PHONY: all clean fclean bonus re $(LIBFTA)
