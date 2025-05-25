CC = gcc
CFLAGS = #-Werror -Wall -Wextra
RM = rm -f

SRC = pipex.c utilities1.c utilities2.c
OBJ = $(SRC:.c=.o)
NAME = pipex

LIBFT_DIR = libft
LIBFT_A = $(LIBTF_DIR)/libft.a

# define target
all: $(LIBTF_A) $(NAME)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR) fclean

re: fclean all

libft_check:
	@echo "Compiling libft..."
	@$(MAKE) -C $(LIBFT_DIR)

test:
	./$(NAME) "file1.txt" "cat -e" "grep fefefesfe" "file2.txt"

.PHONY: all clean fclen re test libft_check
