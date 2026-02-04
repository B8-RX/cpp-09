SOURCES = main.cpp RPN.cpp 

OBJECTS = $(SOURCES:.cpp=.o)

CXX = c++

CXXFLAGS = -Wall -Wextra -Werror -std=c++98
# CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -MMD -MP

HEADERS = RPN.hpp 

NAME = RPN 

# DEPS = $(OBJECTS:.o=.d)

all: $(NAME)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $@

# -include $(DEPS)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

