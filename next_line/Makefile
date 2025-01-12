#Variables
CC = gcc
CFLAGS = -Wall -Werror -Wextra

SRC = get_next_line.c
OBJ = $(SRC:.c=.o)

TEST_FILE = my_test.c
TEST_EXEC = my_test


# Default rule
all: $(TEST_EXEC)

# Rule to create object files from source files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to create the test executable
$(TEST_EXEC): $(TEST_FILE) $(OBJ)
	$(CC) $(CFLAGS) $(TEST_FILE) $(OBJ) -o $(TEST_EXEC)

# Rule to run the test
test: $(TEST_EXEC)
	./$(TEST_EXEC)

clean:
	rm -f $(OBJ) $(TEST_EXEC)
