NAME = cpp_type_infer
CXX = c++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror -Iinclude
SRCS = $(shell find src -name "*.cpp")
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)
clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all