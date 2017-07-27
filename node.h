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


#ifndef __NODE_H_INCLUDE__
#define __NODE_H_INCLUDE__

#include <iostream>
#include <unordered_map>

template <class T>
class WeightedNode {
 public:
    explicit WeightedNode(T v) : value(v) {}
    void addEdge(WeightedNode<T>* node, int weight = 1);
    bool isConnected(WeightedNode<T>* node);
    template <class U>
    friend std::ostream& operator<<(std::ostream& out,
        const WeightedNode<U>& n);
    T value;
    std::unordered_map<WeightedNode<T>*, int> edges;
};

template <class T>
void WeightedNode<T>::addEdge(WeightedNode<T>* node, int weight) {
    edges.insert({node, weight});
}

template <class T>
bool WeightedNode<T>::isConnected(WeightedNode<T>* node) {
    return edges.count(node) == 1;
}

template <class U>
std::ostream& operator<<(std::ostream& out, const WeightedNode<U>& n) {
    for (const auto& edge : n.edges) {
        out << "\t(" << n.value << ", " << edge.first->value << "): "
            << edge.second;
    }
    return out;
}

#endif  // __NODE_H_INCLUDE__
