CXXFLAGS = -std=c++11 -Wall

GRAPH_OBJS = node.o graph.o

all: week1 graph

%.o: %.cpp %.hpp
	clang++ -c -o $@ $< $(CXXFLAGS)

graph: $(GRAPH_OBJS)
	clang++ -o graph graph_test.cpp $(GRAPH_OBJS) $(CXXFLAGS)

week1:
	clang++ -o week1 week1.cpp $(CXXFLAGS)

.PHONY: clean

clean:
	rm -f *.o