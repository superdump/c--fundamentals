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

#include <iostream>
#include <memory>
#include <queue>
#include <random>
#include <tuple>
#include <unordered_set>
#include <vector>

#include "node.hpp"

// WeightedGraph::generate (re)generates a graph of nodes with weighted edges
// n is the number of nodes in the graph
void WeightedGraph::generate(int n, double density, int maxWeight) {
    if (nodes.size() > 0) {
        nodes.clear();
    }

    for (int i = 0; i < n; ++i) {
        // C++14 - nodes.emplace_back(make_unique<WeightedNode>(i));
        nodes.emplace_back(std::unique_ptr<WeightedNode>(new WeightedNode(i)));
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::uniform_real_distribution<double> randomDouble(0.0, 1.0);
    std::uniform_int_distribution<int> randomWeight(0, maxWeight);
    for (const auto& nodeA : nodes) {
        // add random edges with random weights to nodes according to density
        for (const auto& nodeB : nodes) {
            // No loops, no duplicates
            if (nodeA == nodeB || nodeA->connected(nodeB.get()) ||
                    nodeB->connected(nodeA.get())) {
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

std::ostream& operator<<(std::ostream& out,
        const std::unordered_set<WeightedNode*> nodes) {
    for (const auto node : nodes) {
        out << *node << std::endl;
    }
    return out;
}

// WeightedGraph::isConnected checks whether all nodes in the graph have a path
// to each other or not
bool WeightedGraph::isConnected() {
    std::unordered_set<WeightedNode*> open;
    std::unordered_set<WeightedNode*> closed = { nodes[0].get() };

    for (const auto edge : nodes[0]->edges) {
        if (closed.find(edge.first) == closed.end()) {
            open.insert(edge.first);
        }
    }

    while (open.size() > 0) {
        auto node = *open.begin();

        closed.insert(node);
        open.erase(node);

        for (const auto edge : node->edges) {
            if (closed.find(edge.first) == closed.end() &&
                    open.find(edge.first) == open.end()) {
                open.insert(edge.first);
            }
        }
    }

    return nodes.size() == closed.size();
}

typedef std::tuple<std::shared_ptr<TreeNode>, WeightedNode*, int> WeightedEdgeTuple;

class WeightedEdgeComparator {
 public:
    bool operator()(const WeightedEdgeTuple& lhs, const WeightedEdgeTuple& rhs) const {
        return std::get<2>(lhs) > std::get<2>(rhs);
    }
};

int WeightedGraph::dijkstrasShortestPath(const int a, const int b) {
    if (a < 0 || a >= nodes.size() || b < 0 || b >= nodes.size()) {
        return -1;
    }
    if (a == b) {
        return 0;
    }

    std::priority_queue<WeightedEdgeTuple, std::vector<WeightedEdgeTuple>,
        WeightedEdgeComparator> open;
    std::unordered_set<WeightedNode*> closed = {nodes[a].get()};
    std::shared_ptr<TreeNode> root =
        std::make_shared<TreeNode>(nodes[a]->value);

    for (const auto edge : nodes[a]->edges) {
        if (closed.find(edge.first) == closed.end()) {
            std::cout << "Pushing to open: (" << root->value << ", "
                << edge.first->value << ") : " << edge.second << std::endl;
            open.push(std::make_tuple(root, edge.first, edge.second));
        }
    }

    while (open.empty() == false) {
        // take the smallest edge from the priority queue
        auto edge = open.top();
        open.pop();
        auto src = std::get<0>(edge);
        auto dst = std::get<1>(edge);
        auto pathLength = std::get<2>(edge);
        std::cout << "Popped from open: (" << src->value << ", " << dst->value
            << ") : " << pathLength << std::endl;

        std::cout << "Adding (" << src->value << ", " << dst->value <<
            ") to paths tree" << std::endl;
        auto newNode = std::make_shared<TreeNode>(dst->value);
        src->addChild(newNode);

        // if the destination is b, we're done
        if (dst->value == b) {
            std::cout << "Path from " << a << " to " << b << " found:"
                << std::endl;
            std::cout << root << std::endl;
            return pathLength;
        }

        closed.insert(dst);

        // add the destination node's edges to the priority queue if they are
        // not in the closed set
        for (const auto edge : dst->edges) {
            if (closed.find(edge.first) == closed.end()) {
                auto newPathLength = pathLength + edge.second;
                // if not in open set or path is shorter than path in open set
                // then insert into open set
                // NOTE: if the path length is shorter than other paths to the
                // node then this path will have higher priority
                // this means that space is wasted in the priority_queue for
                // worse paths but there doesn't seem to be a way around this
                // without implementing our own data structures
                std::cout << "Pushing to open: (" << newNode->value << ", " <<
                    edge.first->value << ") : " << newPathLength << std::endl;
                open.push(std::make_tuple(newNode, edge.first, newPathLength));
            }
        }
    }

    std::cout << "No path from " << a << " to " << b << std::endl;
    return -1;
}

std::shared_ptr<TreeNode> WeightedGraph::MSTPrim() {
    std::priority_queue<WeightedEdgeTuple, std::vector<WeightedEdgeTuple>,
        WeightedEdgeComparator> open;
    // closed set for fast checking of whether node is in tree
    std::unordered_set<WeightedNode*> closed = {nodes[0].get()};
    // tree for result
    std::shared_ptr<TreeNode> root =
        std::make_shared<TreeNode>(nodes[0]->value);
    int total = 0;

    for (const auto edge : nodes[0]->edges) {
        if (closed.find(edge.first) == closed.end()) {
            std::cout << "Pushing to open: (" << root->value << ", " <<
                edge.first->value << ") : " << edge.second << std::endl;
            open.push(std::make_tuple(root, edge.first, edge.second));
        }
    }

    while (closed.size() < nodes.size() && open.empty() == false) {
        // take the smallest edge from the priority queue
        auto edge = open.top();
        open.pop();
        std::cout << "Popped from open: (" << std::get<0>(edge)->value << ", "
            << std::get<1>(edge)->value << ") : " << std::get<2>(edge)
            << std::endl;

        auto dst = std::get<1>(edge);
        // if the edge is in the tree, skip it
        if (closed.find(dst) != closed.end()) {
            std::cout << "Destination is in tree, skipping." << std::endl;
            continue;
        }
        std::cout << "Adding (" << std::get<0>(edge)->value << ", " <<
            std::get<1>(edge)->value << ") to tree" << std::endl;
        // else insert it into the closed set
        closed.insert(dst);
        // and add it as a child of the appropriate parent node
        auto src = std::get<0>(edge);
        auto newNode = std::make_shared<TreeNode>(dst->value);
        src->addChild(newNode);
        total += std::get<2>(edge);

        // add the destination node's edges to the priority queue if they are
        // not in the closed set
        for (const auto edge : dst->edges) {
            if (closed.find(edge.first) == closed.end()) {
                std::cout << "Pushing to open: (" << newNode->value << ", " <<
                    edge.first->value << ") : " << edge.second << std::endl;
                open.push(std::make_tuple(newNode, edge.first, edge.second));
            }
        }
    }

    if (nodes.size() != closed.size()) {
        std::cout << "No MST" << std::endl;
        return nullptr;
    }
    std::cout << "MST total: " << total << std::endl;

    return root;
}

std::ostream& operator<<(std::ostream& out, const WeightedGraph& g) {
    for (const auto& node : g.nodes) {
        out << *node.get();
        out << std::endl;
    }
    return out;
}
