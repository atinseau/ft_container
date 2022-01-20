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
	@rm -f ft.out std.out
#######################
fclean: clean
	@rm -f $(NAME)
	@rm -f $(TEST_NAME)
#######################
re:
	make fclean
	make all
#######################
test:
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) -D TEST=0
	@./$(NAME) seed_test > std.out
	@$(CC) $(FLAGS) $(OBJS) -o $(NAME) -D TEST=1
	@./$(NAME) seed_test > ft.out
	diff std.out ft.out

#######################
.PHONY: all clean fclean re test