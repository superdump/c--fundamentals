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
#include <vector>

const int N = 40;

template <class T>
inline T sum(std::vector<T> d) {
    T sum = 0;
    // Note: Use a C++11 range for iteration here as we only need the value
    for (auto const& value : d) {
        sum += value;
    }
    return sum;
}

int main() {
    std::vector<int> data(N);

    // Note: iterating using indices just to use the index value in assignment
    // Note 2: Using the ::size_type of the container is more portable than
    // std::size_t and int, hence std::vector<int>::size_type
    for (std::vector<int>::size_type i = 0; i < data.size(); ++i) {
        data[i] = i;
    }

    int accum = sum(data);
    std::cout << "sum is " << accum << std::endl;

    return 0;
}
