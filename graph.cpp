// ISC License
//
// Copyright (c) 2017, Robert Swain <robert.swain@gmail.com>
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include "graph.hpp"

#include "node.hpp"

#include <iostream>
#include <memory>
#include <random>

using namespace std;

// WeightedGraph::generate (re)generates a graph of nodes with weighted edges
// n is the number of nodes in the graph
void WeightedGraph::generate(int n, double density, int maxWeight) {
    if (nodes.size() > 0) {
        nodes.clear();
    }

    for (int i = 0; i < n; ++i) {
        // C++14 - nodes.emplace_back(make_unique<WeightedNode>(i));
        nodes.emplace_back(unique_ptr<WeightedNode>(new WeightedNode(i)));
    }

    random_device rd;
    mt19937 rng(rd());
    uniform_real_distribution<double> randomDouble(0.0, 1.0);
    uniform_int_distribution<int> randomWeight(0, maxWeight);
    for (const auto& nodeA: nodes) {
        // add random edges with random weights to nodes according to density
        for (const auto& nodeB: nodes) {
            // No loops, no duplicates
            if (nodeA == nodeB || nodeA->connected(nodeB.get()) || nodeB->connected(nodeA.get())) {
                continue;
            }
            if (randomDouble(rng) < density) {
                int weight = randomWeight(rng);
                // Bidirectional edges
                nodeA->addEdge(nodeB.get(), weight);
                nodeB->addEdge(nodeA.get(), weight);
            }
        }
    }
}

ostream& operator<<(ostream& out, const WeightedGraph& g) {
    for (const auto& node: g.nodes) {
        out << *node.get();
    }
    return out;
}
