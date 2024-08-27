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

SRC_FILES = pipex.c pipex_units.c
BONUS_SRC_FILES = pipex_bonus.c pipex_units.c read_heredoc.c

LIBFT = libft
LIBFTA = $(LIBFT)/libft.a

SRC_DIR = src

OBJ_DIR = obj
OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))
BONUS_OBJS = $(patsubst %.c, $(OBJ_DIR)/%.o, $(BONUS_SRC_FILES))

ifeq ($(BONUS),1)
TARGET_OBJS = $(BONUS_OBJS)
REMOVE_OBJS = $(filter-out $(BONUS_OBJS), $(OBJS))
else
TARGET_OBJS = $(OBJS)
REMOVE_OBJS = $(filter-out $(OBJS), $(BONUS_OBJS))
endif

NAME = pipex

all: remove-other-obj $(LIBFT) $(NAME)

$(NAME): $(TARGET_OBJS) $(LIBFTA)
	$(CC) $(CFLAGS) -o $@ $^

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -C libft/ bonus

bonus:
	@$(MAKE) BONUS=1 all

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C libft/ fclean
	@rm -f $(NAME)

remove-other-obj:
	@for file in $(REMOVE_OBJS); do \
		if [ -e "$$file" ]; then \
			rm -f "$$file"; \
		fi \
	done

re: fclean all

.DEFAULT_GOAL := all

.PHONY: all clean fclean bonus re $(LIBFT)

