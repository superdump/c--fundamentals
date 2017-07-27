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

#include "hex.h"

Hex::Hex(int width, int height) {
    board.resize(height);
    for (int i = 0; i < height; i++) {
        board[i].resize(width);
        for (int j = 0; j < width; j++) {
            board[i][j] = createNode(static_cast<Color>((i * width + j) % 3));
        }
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // always starting from the top-left and working clockwise
            if (i == 0 && j == 0) {
                // top-left corner
                board[i][j]->addEdge(board[i][j+1]);  // right
                board[i][j]->addEdge(board[i+1][j]);  // bottom-right
            } else if (i == 0 && j == width - 1) {
                // top-right corner
                board[i][j]->addEdge(board[i+1][j]);  // bottom-right
                board[i][j]->addEdge(board[i+1][j-1]);  // bottom-left
                board[i][j]->addEdge(board[i][j-1]);  // left
            } else if (i == height - 1 && j == width - 1) {
                // bottom-right corner
                board[i][j]->addEdge(board[i][j-1]);  // left
                board[i][j]->addEdge(board[i-1][j]);  // top-left
            } else if (i == height - 1 && j == 0) {
                // bottom-left corner
                board[i][j]->addEdge(board[i-1][j]);  // top-left
                board[i][j]->addEdge(board[i-1][j+1]);  // top-right
                board[i][j]->addEdge(board[i][j+1]);  // right
            } else if (i == 0) {
                // top
                board[i][j]->addEdge(board[i][j+1]);  // right
                board[i][j]->addEdge(board[i+1][j]);  // bottom-right
                board[i][j]->addEdge(board[i+1][j-1]);  // bottom-left
                board[i][j]->addEdge(board[i][j-1]);  // left
            } else if (j == width - 1) {
                // right
                board[i][j]->addEdge(board[i-1][j]);  // top-left
                board[i][j]->addEdge(board[i+1][j]);  // bottom-right
                board[i][j]->addEdge(board[i+1][j-1]);  // bottom-left
                board[i][j]->addEdge(board[i][j-1]);  // left
            } else if (i == height - 1) {
                // bottom
                board[i][j]->addEdge(board[i-1][j]);  // top-left
                board[i][j]->addEdge(board[i-1][j+1]);  // top-right
                board[i][j]->addEdge(board[i][j+1]);  // right
                board[i][j]->addEdge(board[i][j-1]);  // left
            } else if (j == 0) {
                // left
                board[i][j]->addEdge(board[i-1][j]);  // top-left
                board[i][j]->addEdge(board[i-1][j+1]);  // top-right
                board[i][j]->addEdge(board[i][j+1]);  // right
                board[i][j]->addEdge(board[i+1][j]);  // bottom-right
            } else {
                // inner
                board[i][j]->addEdge(board[i-1][j]);  // top-left
                board[i][j]->addEdge(board[i-1][j+1]);  // top-right
                board[i][j]->addEdge(board[i][j+1]);  // right
                board[i][j]->addEdge(board[i+1][j]);  // bottom-right
                board[i][j]->addEdge(board[i+1][j-1]);  // bottom-left
                board[i][j]->addEdge(board[i][j-1]);  // left
            }
        }
    }
}

std::ostream& operator<<(std::ostream& out, const Hex& h) {
    int i = 0;
    int j = 0;
    for (const auto& row : h.board) {
        for (int k = 0; k < i; k++) {
            out << " ";
        }
        for (const auto node : row) {
            switch (node->value) {
                case Color::NONE:
                    out << "." << " ";
                    break;
                case Color::BLACK:
                    out << "B" << " ";
                    break;
                case Color::WHITE:
                    out << "W" << " ";
                    break;
            }
            j++;
        }
        out << std::endl;
        i++;
    }
    return out;
}
