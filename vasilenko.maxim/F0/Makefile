CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Wold-style-cast -Wno-missing-field-initializers -O2 -MMD -MP
LDFLAGS =

APP_SRCS = main.cpp System.cpp RTree.cpp Hash_Table.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)
APP_DEPS = $(APP_OBJS:.o=.d)
EXEC = field_analysis

TEST_SRCS = test-rtree.cpp RTree.cpp
TEST_OBJS = $(TEST_SRCS:.cpp=.o)
TEST_DEPS = $(TEST_OBJS:.o=.d)
TEST_EXEC = test_runner

.PHONY: all test clean valgrind-test

all: $(EXEC)

$(EXEC): $(APP_OBJS)
	$(CXX) $(APP_OBJS) -o $(EXEC) $(LDFLAGS)

test: $(TEST_OBJS)
	$(CXX) $(TEST_OBJS) -o $(TEST_EXEC) $(LDFLAGS) -lboost_unit_test_framework
	./$(TEST_EXEC)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d $(EXEC) $(TEST_EXEC)

valgrind-test: test
	valgrind --leak-check=full --error-exitcode=1 --show-leak-kinds=all ./$(TEST_EXEC)

-include $(APP_DEPS) $(TEST_DEPS)
