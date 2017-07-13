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

#include "tree.hpp"

#include <iostream>

void TreeNode::addChild(shared_ptr<TreeNode> node) {
    children.insert(node);
}

bool TreeNode::hasChild(shared_ptr<TreeNode> node) {
    return children.find(node) != children.end();
}

ostream& operator<<(ostream& out, const shared_ptr<TreeNode>& n) {
    for (const auto& child: n->children) {
        out << "\t(" << n->value << ", " << child->value << ")";
        out << child;
    }
    if (n->children.empty()) {
        out << endl;
    }
    return out;
}
