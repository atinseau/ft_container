# AUTO-GENERATE FILE
# BY 42tool
# creator: https://github.com/atinseau
# project author: atinseau
#######################
CC=clang++
NAME=Container

OLD= -std=c++98
FLAGS= -Wall -Wextra -Wall -g -std=c++98

SRCS=	main.cpp test/utils.cpp


#######################
VECTOR_TEST=	test/vector/assign.cpp \
				test/vector/clear.cpp \
				test/vector/constructor.cpp \
				test/vector/erase.cpp \
				test/vector/insert.cpp \
				test/vector/iterator.cpp \
				test/vector/other.cpp \
				test/vector/pop_back.cpp \
				test/vector/push_back.cpp \
				test/vector/reserve.cpp \
				test/vector/resize.cpp

TEST=	test/utils.cpp \
		$(VECTOR_TEST)
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
test: re
	cd containers_test && ./do.sh
# @docker build -t criterion -q test/. &> /dev/null
# @docker run -it --env COMMAND=run_test -v $$PWD:/tmp/project criterion
valgrind:
	@docker build -t criterion -q test/. &> /dev/null
	@docker run -it --env COMMAND=run_valgrind -v $$PWD:/tmp/project criterion

# ONLY IN CONTAINER
run_test:
	@$(CC) $(TEST) -Wall -Wextra -Wall -g -lcriterion -I. -std=c++11 -D C11=1 -o $(TEST_NAME)
	@valgrind ./$(TEST_NAME)
run_valgrind: re
	@valgrind ./$(NAME)


#######################
.PHONY: all clean fclean re test