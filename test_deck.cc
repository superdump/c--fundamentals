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


#include <iostream>

#include "deck.h"
#include "hand.h"

int main() {
    auto deck = Deck();
    std::cout << deck;
    deck.shuffle();
    std::cout << deck;

    int num_iterations;
    std::cout << "How many iterations should be run? ";
    std::cin >> num_iterations;

    int flushes = 0, straights = 0, straight_flushes = 0, four_of_a_kind = 0;
    for (int i = 0; i < num_iterations; i++) {
        deck.shuffle();
        Hand hand(deck.get_top_k(5));
        bool is_flush = hand.is_flush();
        if (is_flush) {
            flushes++;
        }
        bool is_straight = hand.is_straight();
        if (is_straight) {
            straights++;
        }
        if (is_flush && is_straight) {
            straight_flushes++;
        }
        if (hand.is_4_of_a_kind()) {
            four_of_a_kind++;
        }
    }

    std::cout << "Flushes: " << flushes << "/" << num_iterations << std::endl;
    std::cout << "Straights: " << straights << "/" << num_iterations
        << std::endl;
    std::cout << "Straight flushes: " << straight_flushes << "/"
        << num_iterations << std::endl;
    std::cout << "4 of a kind: " << four_of_a_kind << "/"
        << num_iterations << std::endl;
}
