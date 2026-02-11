#Variables
CC = gcc
CFLAGS = #-Wall -Werror -Wextra

SRC = get_next_line_utils.c get_next_line.c
OBJ = $(SRC:.c=.o)

NAME = libgnl.a

# Default rule
all: $(NAME)

# Rule to create object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the test executable
$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean clean
