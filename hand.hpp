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

#ifndef __HAND_HPP_INCLUDE__
#define __HAND_HPP_INCLUDE__

#include <iostream>
#include <vector>

#include "card.hpp"

class Hand {
 public:
    Hand() : hand() {}
    explicit Hand(std::vector<Card> cards) : hand(cards) {}
    friend std::ostream& operator<<(std::ostream& out, const Hand& hand);
    bool is_flush() const;
    bool is_straight() const;
    bool is_straight_flush() const;
 private:
    std::vector<Card> hand;
};

#endif  // __HAND_HPP_INCLUDE__
