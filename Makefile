CXX = g++
CFLAGS = -g3 -fprofile-arcs -ftest-coverage -std=c++20 -Wall -Wextra -Werror
LDFLAGS = -lcriterion

SRC =	Component/And.cpp \
    	Component/clock.cpp \
		Component/false.cpp \
		Component/input.cpp \
		Component/Not.cpp \
		Component/or.cpp \
		Component/output.cpp \
		Component/true.cpp \
		Component/xor.cpp \
		core/circuit.cpp \
		main.cpp \
		Error.cpp \
		ErrorChip.cpp \
		ErrorLink.cpp \
		ErrorOutput.cpp \
		core/ComponentFactory.cpp  

OBJ = $(SRC:.cpp=.o)

TEST_SRC = tests/my_tests.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)

NAME =nanotekspice

all: $(NAME)

$(OBJ): %.o: %.cpp
	$(CXX) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CXX) $(CFLAGS) -o $(NAME) $(OBJ)

clean:
	find . -type f -name '*.o' -delete
	find . -type f -name 'a.out' -delete
	find . -type f -name '*.gcno' -delete
	find . -type f -name '*.gcda' -delete
	find . -type f -name '*.txt' -delete
	find . -type f -name 'unit_tests' -delete
	find . -type f -name 'coding-style-reports.log' -delete

fclean: clean
	rm -f $(NAME)

re: fclean all

tests_run: $(TEST_OBJ) $(filter-out main.o, $(OBJ))
	$(CXX) $(CFLAGS) -o unit_tests $^ $(LDFLAGS)
	./unit_tests; find . -type f -name '*.txt' -delete

coverage:
	gcovr --exclude tests/
