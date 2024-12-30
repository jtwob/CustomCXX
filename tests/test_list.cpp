#include "List.h"
#include <iostream>
#include <cassert>

void test_list() {
    CustomCXX::List<int> list;

    // Test push_front and push_back
    list.push_front(1);
    list.push_back(2);
    list.push_back(3);
    assert(list.size() == 3);
    assert(list.front() == 1);
    assert(list.back() == 3);

    // Test pop_front and pop_back
    list.pop_front();
    assert(list.size() == 2);
    assert(list.front() == 2);

    list.pop_back();
    assert(list.size() == 1);
    assert(list.back() == 2);

    // Test clear
    list.clear();
    assert(list.empty());

    std::cout << "All List tests passed!" << std::endl;
}

int main() {
    test_list();
    return 0;
}