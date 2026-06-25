CXX = g++
CXXFLAGS = -std=c++23 -Wall -Wextra -Wold-style-cast -Wno-missing-field-initializers -O2
LDFLAGS =

APP_SRCS = main.cpp System.cpp RTree.cpp
APP_OBJS = $(APP_SRCS:.cpp=.o)
EXEC = field_analysis

all: $(EXEC)

$(EXEC): $(APP_OBJS)
	$(CXX) $(APP_OBJS) -o $(EXEC) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f *.o $(EXEC)
