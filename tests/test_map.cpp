#include "Map.h"
#include <iostream>
#include <cassert>
#include <string>

void test_map();
void test_erase_and_contains();
void test_basic_operations();
void test_operator_brackets();
void test_erase_single_key();
void test_contains_key_not_present();
void test_rehashing();
void test_insert_or_assign();
void test_keys();

void test_map() {
    test_operator_brackets();
    test_basic_operations();
    test_erase_and_contains();
    test_erase_single_key();
    test_contains_key_not_present();
    test_rehashing();
    test_insert_or_assign();
    test_keys();
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

void test_erase_single_key() {
    CustomCXX::Map<int, std::string> map;

    map[1] = "one";
    map[2] = "two";

    assert(map.contains(1));
    map.erase(1);
    assert(!map.contains(1)); // Should pass
    assert(map.contains(2));  // Other keys should remain intact

    std::cout << "Erase single key test passed!" << std::endl;
}

void test_contains_key_not_present() {
    CustomCXX::Map<int, std::string> map;

    map[1] = "one";

    assert(!map.contains(2)); // Should pass
    std::cout << "Contains key not present test passed!" << std::endl;
}

void test_rehashing() {
    CustomCXX::Map<int, std::string> map(4); // Small initial bucket count
    for (int i = 0; i < 10; ++i) {
        map[i] = "value" + std::to_string(i);
    }

    assert(map.size() == 10); // Ensure all elements are present
    std::cout << "Rehashing test passed!" << std::endl;
}

void test_insert_or_assign() {
    CustomCXX::Map<int, std::string> map;

    map.insert_or_assign(1, "one");
    assert(map.contains(1) && map[1] == "one");

    map.insert_or_assign(1, "uno"); // Update existing key
    assert(map[1] == "uno");

    std::cout << "insert_or_assign test passed!" << std::endl;
}

void test_keys() {
    CustomCXX::Map<int, std::string> map;

    map[1] = "one";
    map[2] = "two";
    map[3] = "three";

    auto key_list = map.keys();
    assert(key_list.size() == 3);
    assert(key_list[0] == 1 || key_list[1] == 1 || key_list[2] == 1);
    assert(key_list[0] == 2 || key_list[1] == 2 || key_list[2] == 2);
    assert(key_list[0] == 3 || key_list[1] == 3 || key_list[2] == 3);

    std::cout << "Keys test passed!" << std::endl;
}

int main() {
    test_map();
    std::cout << "All Map tests passed!" << std::endl;
    return 0;
}