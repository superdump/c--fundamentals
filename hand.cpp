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

#include "hand.hpp"

#include <algorithm>

#include "card.hpp"

std::ostream& operator<<(std::ostream& out, const Hand& hand) {
    for (auto card : hand.hand) {
        out << card << "\t";
    }
    out << std::endl;
    return out;
}

bool Hand::is_flush() const {
    Suit suit = hand[0].get_suit();
    for (auto card = hand.begin() + 1; card != hand.end(); card++) {
        if (suit != card->get_suit()) {
            return false;
        }
    }
    return true;
}

bool Hand::is_straight() const {
    int pips_values[5], i = 0;
    for (auto card : hand) {
        pips_values[i++] = card.get_pips();
    }

    std::sort(pips_values, pips_values + 5);

    if (pips_values[0] == pips_values[1] - 1 &&
        pips_values[1] == pips_values[2] - 1 &&
        pips_values[2] == pips_values[3] - 1 &&
        pips_values[3] == pips_values[4] - 1) {
        return true;
    }

    // handle ace is high case
    if (pips_values[0] == 1 &&
        pips_values[1] == 10 &&
        pips_values[2] == 11 &&
        pips_values[3] == 12 &&
        pips_values[4] == 13) {
        return true;
    }

    return false;
}

bool Hand::is_straight_flush() const {
    return is_flush() && is_straight();
}

bool Hand::is_4_of_a_kind() const {
    int counts[13] = {0, };
    for (auto card : hand) {
        int pips = card.get_pips();
        counts[pips]++;
        if (counts[pips] == 4) {
            return true;
        }
    }
    return false;
}
