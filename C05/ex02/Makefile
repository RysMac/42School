NAME 		= main
CXX			= c++
CXXFLAGS	= -Wall -Werror -Wextra -pedantic -std=c++98


SRCS	= main.cpp Bureaucrat.cpp AForm.cpp ShrubberyCreationForm.cpp
OBJS	= $(SRCS:.cpp=.o)


all: $(NAME)

$(OBJS): Bureaucrat.h AForm.h ShrubberyCreationForm.h

%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re run
