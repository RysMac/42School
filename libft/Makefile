# Variables
CC = gcc
CFLAGS = #-Wall -Wextra -Werror
SRC = 	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c \
		ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c \
		ft_strdup.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
		ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c test.c \
		ft_changechar.c ft_changepointer.c
OBJ = $(SRC:.c=.o)
NAME = test # need to be changed to libft.a later

# Build the program
all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

# Rule to create object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	rm -f $(OBJ)

# Clean both object files and executable
fclean: clean
	rm -f $(NAME)

# Rebuild everything (clean and build)
re: fclean all

# Run the program
run: $(NAME)
	./$(NAME)
