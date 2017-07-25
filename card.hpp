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

#ifndef __CARD_HPP_INCLUDE__
#define __CARD_HPP_INCLUDE__

#include <cassert>
#include <iostream>

enum class Suit {
    SPADES,
    HEARTS,
    DIAMONDS,
    CLUBS
};

class Pips {
 public:
    explicit Pips(int pips) : pips(pips) { assert(pips > 0 && pips < 14); }
    friend std::ostream& operator<<(std::ostream& out, const Pips& pips);
    int get_pips() const { return pips; }
 private:
    int pips;
};

class Card {
 public:
    Card() : suit(Suit::SPADES), pips(1) {}
    Card(Suit suit, Pips pips) : suit(suit), pips(pips) {}
    friend std::ostream& operator<<(std::ostream& out, const Card& card);
    Suit get_suit() const { return suit; }
    int get_pips() const { return pips.get_pips(); }
 private:
    Suit suit;
    Pips pips;
};

#endif  // __CARD_HPP_INCLUDE__
