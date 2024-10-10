# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhiguera <mhiguera@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/09 13:19:19 by mhiguera          #+#    #+#              #
#    Updated: 2024/10/10 18:24:23 by mhiguera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./src/pipex.c ./src/utils.c

OBJS = $(SRC:.c=.o)
C = gcc
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
NAME = pipex
RM = rm -rf

LIBFT_DIR = ./libft/
LIBFT_A = libft.a
LIBFT = -L$(LIBFT_DIR) $(LIBFT_DIR)$(LIBFT_A)

all: $(NAME)
	@$(RM) $(OBJS)

.SILENT: $(OBJS) $(FT_PRINTF)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR) --no-print-directory
	@gcc $(FLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_A) -o $(NAME)

clean:
	@$(RM) $(OBJS)
	@make -C $(LIBFT_DIR) clean --no-print-directory

fclean: clean
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

