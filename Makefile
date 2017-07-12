CXXFLAGS = -std=c++11 -Wall

TEST_BIN = week1 test_graph
TEST_GRAPH_OBJS = node.o graph.o


all: $(TEST_BIN)

%.o: %.cpp %.hpp
	clang++ -c -o $@ $< $(CXXFLAGS)

test_graph: test_graph.cpp $(TEST_GRAPH_OBJS)
	clang++ -o test_graph test_graph.cpp $(TEST_GRAPH_OBJS) $(CXXFLAGS)

week1:
	clang++ -o week1 week1.cpp $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o $(TEST_BIN)
