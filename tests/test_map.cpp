#include "Map.h"
#include <iostream>
#include <cassert>

void test_map();
void test_erase_and_contains();
void test_basic_operations();
void test_operator_brackets();

void test_map() {
    test_operator_brackets();
    test_basic_operations();
    test_erase_and_contains();
}

void test_basic_operations() {
    CustomCXX::Map<int, std::string> map;

    // Insert and access elements
    map[1] = "one";
    map[2] = "two";

    assert(map[1] == "one");
    assert(map[2] == "two");

    // Check size
    assert(map.size() == 2);

    // Overwrite a value
    map[1] = "uno";
    assert(map[1] == "uno");

    std::cout << "Basic operations test passed!" << std::endl;
}

void test_erase_and_contains() {
    CustomCXX::Map<int, std::string> map;

    map[1] = "one";
    map[2] = "two";
    map[3] = "three";

    // Erase an element
    map.erase(2);
    assert(!map.contains(2));

    // Check remaining elements
    assert(map.contains(1));
    assert(map.contains(3));

    std::cout << "Erase and contains test passed!" << std::endl;
}

void test_operator_brackets() {
    CustomCXX::Map<int, std::string> map;
    map[1] = "one";
    assert(map[1] == "one");
    std::cout << "Operator[] test passed!" << std::endl;
}

int main() {
    test_map();
    std::cout << "All Map tests passed!" << std::endl;
    return 0;
}