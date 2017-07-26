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

#include "card.h"

std::ostream& operator<<(std::ostream& out, const Suit& suit) {
    switch (suit) {
        case Suit::SPADES:
            out << "S";
            break;
        case Suit::HEARTS:
            out << "H";
            break;
        case Suit::DIAMONDS:
            out << "D";
            break;
        case Suit::CLUBS:
            out << "C";
            break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Pips& pips) {
    switch (pips.pips) {
        case 1:
            out << "A";
            break;
        case 11:
            out << "J";
            break;
        case 12:
            out << "Q";
            break;
        case 13:
            out << "K";
            break;
        default:
            out << pips.pips;
            break;
    }
    return out;
}

std::ostream& operator<<(std::ostream& out, const Card& card) {
    out << card.suit << card.pips;
    return out;
}
