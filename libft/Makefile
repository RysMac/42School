# Variables
CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -f
SRC = 	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
		ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
		ft_atoi.c ft_calloc.c ft_strdup.c \
		ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c \
		ft_putendl_fd.c ft_putnbr_fd.c \
		ft_changechar.c ft_changepointer.c
BONUS_SRC = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c
OBJ = $(SRC:.c=.o)
BONUS_OBJ = $(BONUS_SRC:.c=.o)
NAME = libft.a
TEST_FILE = test.c
TEST_EXEC = test_program

# Default rule
all: $(NAME)

# Rule to build the library
$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)

# Rule for bonus files
bonus: $(BONUS_OBJ)
	$(AR) $(NAME) $(BONUS_OBJ)

# Rule to create object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJ) $(BONUS_OBJ)

# Clean both object files and the library
fclean: clean
	$(RM) $(NAME) $(TEST_EXEC)

# Rebuild everything
re: fclean all

# Rule to test the library using test.c
test: $(NAME) $(TEST_FILE)
	$(CC) $(CFLAGS) -o $(TEST_EXEC) $(TEST_FILE) $(NAME)
	./$(TEST_EXEC)
