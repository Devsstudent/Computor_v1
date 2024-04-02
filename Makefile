NAME = computor
CC = gcc
SRC = main.c
OBJ = main.o
CFLAGS = -Wall -Werror -Wextra -g3

all : $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -I ./ $(OBJ) -o $(NAME)

$(OBJ):
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY:
	clean fclean re all
