CC = gcc
CFLAGS = -Iincludes -Imlx -g #-Werror -Wall -Wextra
RM = rm -f
MLX_DIR = mlx
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

NEXT_LINE_DIR = get_next_line
NEXT_LINE = $(NEXT_LINE_DIR)/libgnl.a

SRC = main_read.c utils_basic.c utils_grid.c utils_mlx.c utils_fit.c
OBJ = $(SRC:.c=.o)
NAME = fdf

all: $(LIBFT_A) $(NEXT_LINE) $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(NEXT_LINE):
	$(MAKE) -C $(NEXT_LINE_DIR)

$(NAME): $(OBJ) $(NEXT_LINE)
	$(CC) $(CFLAGS) $(OBJ) $(MLX_FLAGS) -L$(NEXT_LINE_DIR) -lgnl -L$(LIBFT_DIR) -lft -o $(NAME)

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(NEXT_LINE_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) fclean -C $(NEXT_LINE_DIR) fclean
	$(MAKE) fclean -C $(LIBFT_DIR) fclean

re: fclean all
