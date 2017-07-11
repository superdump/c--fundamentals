#include <iostream>
#include <vector>

using namespace std;

const int N = 40;

template <class T>
inline T sum(vector<T> d) {
    T sum = 0;
    // Note: Use a C++11 range for iteration here as we only need the value
    for (auto const& value: d) {
        sum += value;
    }
    return sum;
}

int main() {
    vector<int> data(N);

    // Note: iterating using indices just to use the index value in assignment
    // Note 2: Using the ::size_type of the container is more portable than
    // std::size_t and int, hence vector<int>::size_type
    for (vector<int>::size_type i = 0; i < data.size(); ++i) {
        data[i] = i;
    }

    int accum = sum(data);
    cout << "sum is " << accum << endl;

    return 0;
}
