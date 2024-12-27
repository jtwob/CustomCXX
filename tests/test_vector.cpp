#include "Vector.h"
#include <iostream>
#include <cassert>

void test_vector() {
    CustomCXX::Vector<int> vec;
    vec.push_back(42);
    vec.push_back(13);

    assert(vec[0] == 42);
    assert(vec[1] == 13);

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    test_vector();
    return 0;
}