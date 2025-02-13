CC = gcc
CFLAGS = -Wall -Werror -Wextra -Iinclude
AR = ar rcs
RM = rm -f

SRC = src/ft_printf.c src/utils.c
OBJ = $(SRC:.c=.o)

SRC_TEST = src/main.c
OBJ_TEST = $(SRC_TEST:.c=.o)

NAME = libftprintf.a
NAME_TEST = my_program

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ) $(OBJ_TEST)

fclean: clean
	$(RM) $(NAME) $(NAME_TEST)

re: fclean all

test: $(NAME) $(OBJ_TEST)
	$(CC) $(CFLAGS) -o $(NAME_TEST) $(OBJ_TEST) $(NAME)
	./$(NAME_TEST)

.PHONY: all clean fclean re test
