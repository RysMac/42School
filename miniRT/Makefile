CC		:= gcc
CFLAGS	:= # -Wall -Wextra -Werror
INCS	:= -Iinclude
SRCS	:= src/algebra.c src/frame.c src/coloring.c src/camera.c \
			src/helper1.c src/shade.c \
			src/build_plane.c src/build_cylinder.c src/build_sphere.c \
			src/ppm_write.c src/ray_dir.c  main.c

# libraries
LDLIBS  := -lm

NAME	:= ppm_test

OBJS	:= $(SRCS:.c=.o)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

test:
	./$(NAME)

ret: re test

testvalg:
	valgrind ./$(NAME)

testvalgfull:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean re test testvalg testvalgfull