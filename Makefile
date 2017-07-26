CXXFLAGS = -std=c++11 -Wall

TEST_BIN = \
	test_deck \
	test_dijkstras \
	test_graph \
	test_mst \
	week1


all: $(TEST_BIN)

%.o: %.cc %.h
	clang++ -c -o $@ $< $(CXXFLAGS)


TEST_GRAPH_OBJS = \
	node.o \
	graph.o \
	tree.o

test_graph: test_graph.cc $(TEST_GRAPH_OBJS)
	clang++ -o test_graph test_graph.cc $(TEST_GRAPH_OBJS) $(CXXFLAGS)


TEST_MST_OBJS = \
	node.o \
	graph.o \
	tree.o

test_mst: test_mst.cc $(TEST_MST_OBJS)
	clang++ -o test_mst test_mst.cc $(TEST_MST_OBJS) $(CXXFLAGS)

TEST_DIJKSTRAS_OBJS = \
	node.o \
	graph.o \
	tree.o

test_dijkstras: test_dijkstras.cc $(TEST_DIJKSTRAS_OBJS)
	clang++ -o test_dijkstras test_dijkstras.cc $(TEST_DIJKSTRAS_OBJS) $(CXXFLAGS)

CARD_OBJS = \
	card.o \
	deck.o \
	hand.o

test_deck: test_deck.cc $(CARD_OBJS)
	clang++ -o test_deck test_deck.cc $(CARD_OBJS) $(CXXFLAGS)

week1:
	clang++ -o week1 week1.cc $(CXXFLAGS)


.PHONY: clean

clean:
	rm -f *.o $(TEST_BIN)
