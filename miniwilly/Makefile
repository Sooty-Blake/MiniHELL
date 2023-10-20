NAME = exe

COMPILE = gcc

FLAGS =

SRCS = *.c

LIBS = -lreadline

all: $(NAME)

$(NAME):
	$(COMPILE) $(FLAGS) $(SRCS) -o $(NAME) $(LIBS)

clean:
	rm -f $(NAME)

re: clean all

.PHONY: all clean re