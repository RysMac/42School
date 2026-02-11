CC		:= gcc -g
CFLAGS	:= -lgnl -lft #-Wall -Wextra -Werror
INCS	:= -Iinclude
SRCS	:= src/algebra.c src/frame.c src/coloring.c src/coloring_mlx.c \
		src/hooks.c src/camera.c src/helper1.c src/shade.c \
		src/build_plane.c src/build_cylinder.c src/build_sphere.c \
		src/ppm_write.c src/ray_dir.c  \
		src/parse_ambient.c src/parse_camera.c src/parse_cylinder.c \
		src/parse_error.c src/parse_light.c src/parse_line.c src/parse_plane.c \
		src/parse_sphere.c src/parse_utils.c src/parse.c \
		main.c

NAME	:= ppm_test

# libraries
LIBFT_DIR := libft
GNL_DIR   := get_next_line
LIBFT_A := $(LIBFT_DIR)/libft.a
GNL_A   := $(GNL_DIR)/libgnl.a
MLX_DIR := minilibx-linux
MLX_FLAGS := -L$(MLX_DIR) -lmlx -lXext -lX11


LDLIBS  := -lm -L$(GNL_DIR) -L$(LIBFT_DIR)

OBJS	:= $(SRCS:.c=.o)

all: $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL_A):
	$(MAKE) -C $(GNL_DIR)

$(NAME): $(OBJS) $(LIBFT_A) $(GNL_A)
	$(CC) $(OBJS) $(MLX_FLAGS) $(CFLAGS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

clean:
	rm -f $(OBJS)
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(GNL_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

test:
	./$(NAME) test.rt

ret: re test

testvalg:
	valgrind ./$(NAME) test.rt

testvalgfull:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME) test.rt

.PHONY: all clean fclean re test testvalg testvalgfull
