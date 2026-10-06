NAME		= test

CXX			= c++
CXXFLAGS	= -Wall -Wextra #-Werror -std=c++98

SOCK_DIR	= ../Sockets
SRCS		= test.cpp \
			  TestServer.cpp \
			  SimpleServer.cpp \
			  $(SOCK_DIR)/SimpleSocket.cpp \
			  $(SOCK_DIR)/BindingSocket.cpp \
			  $(SOCK_DIR)/ListeningSocket.cpp \
			  $(SOCK_DIR)/ConnectingSocket.cpp
OBJS		= $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(NAME)
	./$(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all run clean fclean re
