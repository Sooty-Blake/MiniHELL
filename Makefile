# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bburston <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 13:25:35 by bburston          #+#    #+#              #
#    Updated: 2023/09/18 20:44:42 by bburston         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIBFT = libft/libft.a

HEADER = ./includes/

CC = gcc


FLAGS = -Wextra -Werror -Wall -Iincludes -Iusr/local/opt/readline/include/

SRCS = srcs/*.c \

OBJECTS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(FLAGS) $(SRCS) $(LIBFT) -I $(HEADER) -o $(NAME) -L /usr/local/opt/readline/lib -lreadline
	@echo Minishell has been made.

$(LIBFT):
	@make -C ./libft

clean:
	@rm -f $(OBJECTS)
	@make clean -C ./libft
	@echo Clean.

fclean: clean
	@rm -f $(NAME)
	@make fclean -C ./libft
	@echo Very clean.


re: fclean all

.PHONY: all clean fclean re