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


#ifndef __TREE_NODE_HPP_INCLUDE__
#define __TREE_NODE_HPP_INCLUDE__

#include <memory>
#include <unordered_set>

using namespace std;

class TreeNode {
public:
    unordered_set<shared_ptr<TreeNode> > children;
    int value;
    TreeNode():children(), value(0) {}
    TreeNode(int v = 0):children(), value(v) {}
    void addChild(shared_ptr<TreeNode> node);
    bool hasChild(shared_ptr<TreeNode> node);
    friend ostream& operator<<(ostream& out, const shared_ptr<TreeNode>& n);
};

#endif // __TREE_NODE_HPP_INCLUDE__
