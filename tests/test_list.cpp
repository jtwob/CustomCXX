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

void test_insert() {
    CustomCXX::List<int> list;

    // Insert into an empty list
    list.insert(0, 1);
    assert(list.size() == 1);
    assert(list.front() == 1);

    // Insert at the beginning
    list.insert(0, 0);
    assert(list.front() == 0);

    // Insert in the middle
    list.insert(1, 2);
    assert(list.at(1) == 2);

    // Insert at the end
    list.insert(3, 3);
    assert(list.back() == 3);

    std::cout << "Insert tests passed!" << std::endl;
}

void test_erase() {
    CustomCXX::List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Erase from the beginning
    list.erase(0);
    assert(list.front() == 2);
    assert(list.size() == 2);

    // Erase from the middle
    list.push_back(4);
    list.erase(1); // Should remove the element "3"
    assert(list.at(1) == 4);

    // Erase from the end
    list.pop_back();
    assert(list.back() == 2);
    assert(list.size() == 1);

    std::cout << "Erase tests passed!" << std::endl;
}

// void test_erase() {
//     CustomCXX::List<int> list;
//     list.push_back(1);
//     list.push_back(2);
//     list.push_back(3);

//     // Erase from the beginning
//     list.erase(0); // Removes "1"
//     assert(list.size() == 2);
//     assert(list.at(0) == 2);

//     // Erase from the middle
//     list.push_back(4); // [2, 3, 4]
//     list.erase(1);     // Removes "3"
//     assert(list.size() == 2);
//     assert(list.at(0) == 2);
//     assert(list.at(1) == 4);

//     // Erase from the end
//     list.pop_back(); // Removes "4"
//     assert(list.size() == 1);
//     assert(list.back() == 2);

//     std::cout << "Erase tests passed!" << std::endl;
// }

void test_reverse() {
    CustomCXX::List<int> list;

    // Reverse an empty list
    list.reverse();
    assert(list.size() == 0);

    // Reverse a single-element list
    list.push_back(1);
    list.reverse();
    assert(list.front() == 1 && list.back() == 1);

    // Reverse a multi-element list
    list.push_back(2);
    list.push_back(3);
    list.reverse();
    assert(list.front() == 3 && list.back() == 1);

    std::cout << "Reverse tests passed!" << std::endl;
}

void test_iterators() {
    CustomCXX::List<int> list = {1, 2, 3};

    // Forward iteration
    int expected = 1;
    for (auto node = list.begin(); node != list.end(); node = node->next) {
        assert(node->value == expected++);
    }

    // Reverse iteration
    expected = 3;
    for (auto node = list.rbegin(); node != list.rend(); node = node->prev) {
        assert(node->value == expected--);
    }

    std::cout << "Iterator tests passed!" << std::endl;
}

int main() {
    test_list();
    test_insert();
    test_erase();
    test_reverse();
    test_iterators();
    return 0;
}