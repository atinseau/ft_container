# AUTO-GENERATE FILE
# BY 42tool
# creator: https://github.com/atinseau
# project author: atinseau
#######################
CC=clang++
NAME=Container

OLD= -std=c++98
FLAGS= -Wall -Wextra -Wall -g -std=c++98

SRCS=	main.cpp
TEST= test/vector.cpp
TEST_NAME= test.out
#######################
OBJS=${SRCS:.cpp=.o}
#######################
.cpp.o:
	$(CC) $(FLAGS) -c $< -o ${<:.cpp=.o}
#######################
$(NAME): $(OBJS)
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME)
#######################
all: $(NAME)
#######################
clean:
	@rm -f $(OBJS)
#######################
fclean: clean
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)
#######################
re: fclean all
#######################
.PHONY: all clean fclean re

test: fclean
	@$(CC) $(TEST) -Wall -Wextra -Wall -g -lcriterion -o $(TEST_NAME)
	@./$(TEST_NAME)
	
