NAME = minishell

LIBFT = libft/libft.a

HEADER = ./includes/

CC = gcc


FLAGS = 

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