CC = gcc
CFLAGS = #-Werror -Wall -Wextra
RM = rm -f

SRC = main.c utilis_list.c utilis_swap.c utilis_push.c utilis_rot.c utilis_revrot.c utilis_sort.c utilis_small.c utilis_basic.c
OBJ = $(SRC:.c=.o)
NAME = push_swap

# define target
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

test:
	./$(NAME)

leaks:
	valgrind ./$(NAME)

.PHONY: all clean fclen re test leaks
