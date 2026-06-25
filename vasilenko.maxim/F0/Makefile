CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Wold-style-cast -Wno-missing-field-initializers -O2
LDFLAGS =

APP_SRCS = main.cpp System.cpp RTree.cpp Hash_Table.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)
EXEC = field_analysis

TEST_SRCS = test-rtree.cpp RTree.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_EXEC = test_runner

all: $(EXEC)

$(EXEC): $(APP_OBJS)
	$(CXX) $(APP_OBJS) -o $(EXEC) $(LDFLAGS)

test: $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) -o $(TEST_EXEC) $(LDFLAGS)
	./$(TEST_EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC) $(TEST_EXEC)

valgrind-test: test
	valgrind --leak-check=full --error-exitcode=1 --show-leak-kinds=all ./$(TEST_EXEC)
