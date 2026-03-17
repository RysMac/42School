CC        := gcc

MLX_DIR   := minilibx-linux
LIBFT_DIR := libft
GNL_DIR   := get_next_line

NAME      := test

SRCS := src/algebra.c src/frame.c src/coloring.c src/camera.c \
        src/helper1.c src/shade.c \
        src/build_plane.c src/build_cylinder.c src/build_sphere.c \
        src/ppm_write.c src/ray_dir.c \
		src/hooks.c src/parse_ambient.c src/parse_camera.c src/parse_cylinder.c \
		src/parse_error.c src/parse_light.c src/parse_line.c src/parse_plane.c \
		src/parse_sphere.c src/parse_utils.c src/parse.c \
		src/main.c

OBJS := $(SRCS:.c=.o)

LIBFT_A := $(LIBFT_DIR)/libft.a
GNL_A   := $(GNL_DIR)/libgnl.a

# compile flags
CPPFLAGS := -Iinclude -I$(MLX_DIR)
CFLAGS   := -Wall -Wextra -Werror -MMD -MP

# link flags
LDFLAGS  := -L$(MLX_DIR) -L$(GNL_DIR) -L$(LIBFT_DIR)
LDLIBS   := -lmlx -lXext -lX11 -lgnl -lft -lm

DEPS := $(OBJS:.o=.d)
-include $(DEPS)

all: $(NAME)

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_DIR)

$(GNL_A):
	$(MAKE) -C $(GNL_DIR)

$(NAME): $(OBJS) $(LIBFT_A) $(GNL_A)
	$(CC) $(OBJS) $(LDFLAGS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS)
	$(MAKE) -C $(GNL_DIR) clean
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(GNL_DIR) fclean
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

run: $(NAME)
	./$(NAME)

valgrind: $(NAME)
	valgrind ./$(NAME)

valgrindfull: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re run valgrind valgrindfull
