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
#include <queue>
#include <random>
#include <unordered_set>

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

ostream& operator<<(ostream& out, const unordered_set<WeightedNode*> nodes) {
    for (const auto node: nodes) {
        out << *node << endl;
    }
    return out;
}

// WeightedGraph::isConnected checks whether all nodes in the graph have a path
// to each other or not
bool WeightedGraph::isConnected() {
    unordered_set<WeightedNode*> open;
    unordered_set<WeightedNode*> closed = {nodes[0].get()};

    for (const auto edge: nodes[0]->edges) {
        if (closed.find(edge.first) == closed.end()) {
            open.insert(edge.first);
        }
    }

    while (open.size() > 0) {
        auto node = *open.begin();

        closed.insert(node);
        open.erase(node);

        for (const auto edge: node->edges) {
            if (closed.find(edge.first) == closed.end() && open.find(edge.first) == open.end()) {
                open.insert(edge.first);
            }
        }
    }

    return nodes.size() == closed.size();
}

class EdgeComparator {
public:
    bool operator()(tuple<shared_ptr<TreeNode>, WeightedNode*, int>& lhs, tuple<shared_ptr<TreeNode>, WeightedNode*, int>& rhs) const {
        return get<2>(lhs) > get<2>(rhs);
    }
};

int WeightedGraph::dijkstrasShortestPath(const int a, const int b) {
    if (a < 0 || a >= nodes.size() || b < 0 || b >= nodes.size()) {
        return -1;
    }
    if (a == b) {
        return 0;
    }

    priority_queue<tuple<shared_ptr<TreeNode>, WeightedNode*, int>, vector<tuple<shared_ptr<TreeNode>, WeightedNode*, int> >, EdgeComparator> open;
    unordered_set<WeightedNode*> closed = {nodes[a].get()};
    shared_ptr<TreeNode> root = make_shared<TreeNode>(nodes[a]->value);

    for (const auto edge: nodes[a]->edges) {
        if (closed.find(edge.first) == closed.end()) {
            cout << "Pushing to open: (" << root->value << ", " << edge.first->value << ") : " << edge.second << endl;
            open.push(make_tuple(root, edge.first, edge.second));
        }
    }

    while (open.empty() == false) {
        // take the smallest edge from the priority queue
        auto edge = open.top();
        open.pop();
        auto src = get<0>(edge);
        auto dst = get<1>(edge);
        auto pathLength = get<2>(edge);
        cout << "Popped from open: (" << src->value << ", " << dst->value << ") : " << pathLength << endl;

        cout << "Adding (" << src->value << ", " << dst->value << ") to paths tree" << endl;
        auto newNode = make_shared<TreeNode>(dst->value);
        src->addChild(newNode);

        // if the destination is b, we're done
        if (dst->value == b) {
            cout << "Path from " << a << " to " << b << " found:" << endl;
            cout << root << endl;
            return pathLength;
        }

        closed.insert(dst);

        // add the destination node's edges to the priority queue if they are not in the closed set
        for (const auto edge: dst->edges) {
            if (closed.find(edge.first) == closed.end()) {
                auto newPathLength = pathLength + edge.second;
                // if not in open set or path is shorter than path in open set then insert into open set
                // NOTE: if the path length is shorter than other paths to the node then this path will have higher priority
                // this means that space is wasted in the priority_queue for worse paths but there doesn't seem to be a way around this
                // without implementing our own data structures
                cout << "Pushing to open: (" << newNode->value << ", " << edge.first->value << ") : " << newPathLength << endl;
                open.push(make_tuple(newNode, edge.first, newPathLength));
            }
        }
    }

    cout << "No path from " << a << " to " << b << endl;
    return -1;
}

shared_ptr<TreeNode> WeightedGraph::MSTPrim() {
    priority_queue<tuple<shared_ptr<TreeNode>, WeightedNode*, int>, vector<tuple<shared_ptr<TreeNode>, WeightedNode*, int> >, EdgeComparator> open;
    // closed set for fast checking of whether node is in tree
    unordered_set<WeightedNode*> closed = {nodes[0].get()};
    // tree for result
    shared_ptr<TreeNode> root = make_shared<TreeNode>(nodes[0]->value);
    int total = 0;

    for (const auto edge: nodes[0]->edges) {
        if (closed.find(edge.first) == closed.end()) {
            cout << "Pushing to open: (" << root->value << ", " << edge.first->value << ") : " << edge.second << endl;
            open.push(make_tuple(root, edge.first, edge.second));
        }
    }

    while (closed.size() < nodes.size() && open.empty() == false) {
        // take the smallest edge from the priority queue
        auto edge = open.top();
        open.pop();
        cout << "Popped from open: (" << get<0>(edge)->value << ", " << get<1>(edge)->value << ") : " << get<2>(edge) << endl;

        auto dst = get<1>(edge);
        // if the edge is in the tree, skip it
        if (closed.find(dst) != closed.end()) {
            cout << "Destination is in tree, skipping." << endl;
            continue;
        }
        cout << "Adding (" << get<0>(edge)->value << ", " << get<1>(edge)->value << ") to tree" << endl;
        // else insert it into the closed set
        closed.insert(dst);
        // and add it as a child of the appropriate parent node
        auto src = get<0>(edge);
        auto newNode = make_shared<TreeNode>(dst->value);
        src->addChild(newNode);
        total += get<2>(edge);

        // add the destination node's edges to the priority queue if they are not in the closed set
        for (const auto edge: dst->edges) {
            if (closed.find(edge.first) == closed.end()) {
                cout << "Pushing to open: (" << newNode->value << ", " << edge.first->value << ") : " << edge.second << endl;
                open.push(make_tuple(newNode, edge.first, edge.second));
            }
        }
    }

    if (nodes.size() != closed.size()) {
        cout << "No MST" << endl;
        return nullptr;
    }
    cout << "MST total: " << total << endl;

    return root;
}

ostream& operator<<(ostream& out, const WeightedGraph& g) {
    for (const auto& node: g.nodes) {
        out << *node.get();
        out << endl;
    }
    return out;
}
