# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhiguera <mhiguera@student.42madrid.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/04 12:09:52 by mhiguera          #+#    #+#              #
#    Updated: 2024/06/04 12:13:04 by mhiguera         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = ./src/pipex.c ./src/utils.c

OBJS = $(SRC:.c=.o)
C = gcc
FLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address
NAME = pipex
RM = rm -rf

LIBFT_DIR = ./libft/
LIBFT_A = libft.a
LIBFT = -L$(LIBFT_DIR) $(LIBFT_DIR)$(LIBFT_A)

all: $(NAME)
	@$(RM) $(OBJS)

.SILENT: $(OBJS) $(FT_PRINTF)

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@gcc $(FLAGS) $(OBJS) $(LIBFT_DIR)$(LIBFT_A) -o $(NAME)

clean:
	@$(RM) $(OBJS) $(LIBFT)
	@make clean -C $(LIBFT_DIR)

fclean:	clean
	@make fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME) $(OBJS)

re:	fclean all
	
.PHONY:	all clean fclean re