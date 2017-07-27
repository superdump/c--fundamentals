CXXFLAGS = -std=c++11 -Wall

TEST_BIN = \
	test_deck \
	test_dijkstras \
	test_graph \
	test_hex \
	test_mst \
	week1


all: $(TEST_BIN)

%.o: %.cc %.h
	clang++ -c -o $@ $< $(CXXFLAGS)


GRAPH_OBJS = \
	node.o \
	graph.o \
	tree.o

test_graph: test_graph.cc $(GRAPH_OBJS)
	clang++ -o test_graph test_graph.cc $(GRAPH_OBJS) $(CXXFLAGS)


test_mst: test_mst.cc $(GRAPH_OBJS)
	clang++ -o test_mst test_mst.cc $(GRAPH_OBJS) $(CXXFLAGS)

test_dijkstras: test_dijkstras.cc $(GRAPH_OBJS)
	clang++ -o test_dijkstras test_dijkstras.cc $(GRAPH_OBJS) $(CXXFLAGS)

HEX_OBJS = \
	$(GRAPH_OBJS) \
	hex.o

test_hex: test_hex.cc $(HEX_OBJS)
	clang++ -o test_hex test_hex.cc $(HEX_OBJS) $(CXXFLAGS)


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
