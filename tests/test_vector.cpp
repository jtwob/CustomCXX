#include "Vector.h"
#include <iostream>
#include <cassert>

void test_initialization();
void test_push_back();
void test_pop_back();
void test_subscript_operator();
void test_iterators();
void test_clear();
void test_insert();
void test_erase();
void test_move_semantics();

void test_vector() {
    test_initialization();
    test_push_back();
    test_pop_back();
    test_subscript_operator();
    test_iterators();
    test_clear();
    test_insert();
    test_erase();
    test_move_semantics();
    test_copy_constructor();
    test_copy_assignment();
    test_reserve();
    test_shrink_to_fit();
    test_reverse_iterators();
    std::cout << "All tests passed!" << std::endl;
}

void test_initialization() {
    CustomCXX::Vector<int> vec;
    assert(vec.size() == 0);
    assert(vec.capacity() == 0);
    std::cout << "Initialization tests passed!" << std::endl;
}

void test_push_back() {
    CustomCXX::Vector<int> vec;

    vec.push_back(1);
    assert(vec.size() == 1);

    size_t initial_capacity = vec.capacity();
    vec.push_back(2);

    // Handle edge case where initial capacity is 0
    if (initial_capacity == 0) {
        assert(vec.capacity() == 1); // First resize sets capacity to 1
    } else {
        assert(vec.capacity() > initial_capacity);
    }

    assert(vec[0] == 1);
    assert(vec[1] == 2);

    std::cout << "Push_back tests passed!" << std::endl;
}

void test_pop_back() {
    CustomCXX::Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    vec.pop_back();
    assert(vec.size() == 2);
    assert(vec[1] == 2);

    // Try popping all elements
    vec.pop_back();
    vec.pop_back();
    assert(vec.size() == 0);

    // Ensure exception is thrown for underflow
    try {
        vec.pop_back();
        assert(false); // Should not reach here
    } catch (const std::underflow_error& e) {
        assert(std::string(e.what()) == "Vector is empty");
    }

    std::cout << "Pop_back tests passed!" << std::endl;
}

void test_subscript_operator() {
    CustomCXX::Vector<int> vec = {1, 2, 3};
    assert(vec[0] == 1);
    assert(vec[1] == 2);
    assert(vec[2] == 3);

    vec[0] = 10;
    assert(vec[0] == 10);

    // Ensure out-of-range access throws an exception
    try {
        int x = vec[10]; // Should throw
        assert(false);   // Should not reach here
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Index out of range");
    }

    std::cout << "Subscript operator tests passed!" << std::endl;
}

void test_iterators() {
    CustomCXX::Vector<int> vec = {1, 2, 3};
    int sum = 0;

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        sum += *it;
    }

    assert(sum == 6);

    std::cout << "Iterator tests passed!" << std::endl;
}

void test_clear() {
    CustomCXX::Vector<int> vec = {1, 2, 3, 4, 5};
    vec.clear();
    assert(vec.size() == 0);
    assert(vec.capacity() > 0); // Capacity should remain unchanged

    // Ensure accessing elements throws an error
    try {
        int x = vec[0];
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Index out of range");
    }

    std::cout << "Clear tests passed!" << std::endl;
}

void test_insert() {
    CustomCXX::Vector<int> vec = {1, 2, 4, 5};

    // Insert in the middle
    vec.insert(2, 3);
    assert(vec[2] == 3);
    assert(vec[3] == 4);
    assert(vec.size() == 5);

    // Insert at the beginning
    vec.insert(0, 0);
    assert(vec[0] == 0);
    assert(vec.size() == 6);

    // Insert at the end
    vec.insert(vec.size(), 6);
    assert(vec[vec.size() - 1] == 6);

    // Handle invalid indices
    try {
        vec.insert(10, 99);
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Index out of range");
    }

    std::cout << "Insert tests passed!" << std::endl;
}

void test_erase() {
    CustomCXX::Vector<int> vec = {1, 2, 3, 4, 5};

    // Erase middle element
    vec.erase(2);
    assert(vec[2] == 4);
    assert(vec.size() == 4);

    // Erase first element
    vec.erase(0);
    assert(vec[0] == 2);
    assert(vec.size() == 3);

    // Erase last element
    vec.erase(vec.size() - 1);
    assert(vec.size() == 2);

    // Handle invalid indices
    try {
        vec.erase(10);
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Index out of range");
    }

    std::cout << "Erase tests passed!" << std::endl;
}

void test_move_semantics() {
    CustomCXX::Vector<int> vec1 = {1, 2, 3};
    CustomCXX::Vector<int> vec2 = std::move(vec1);

    // Ensure vec2 has taken ownership of vec1's data
    assert(vec2.size() == 3);
    assert(vec2[0] == 1);

    // Ensure vec1 is empty
    assert(vec1.size() == 0);
    try {
        int x = vec1[0];
        assert(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        assert(std::string(e.what()) == "Index out of range");
    }

    std::cout << "Move semantics tests passed!" << std::endl;
}

void test_copy_constructor(){
    CustomCXX::Vector<int> vec = {1, 2, 3};
    CustomCXX::Vector<int> copy(vec);

    // Ensure copy has the same elements;
    assert(copy.size() == vec.size());
    for(size_t i = 0; i < vec.size(); ++i){
        assert(copy[i] == vec[i]);
    }

    // Ensure deep copy
    copy[0] = 10;
    assert(copy[0] != vec[0]);

    std::cout << "Copy constructor tests passed!" << std::endl;
}

void test_copy_assignment(){
    CustomCXX::Vector<int> vec = {1, 2, 3};
    CustomCXX::Vector<int> copy;
    copy = vec;

    // Ensure copy has the same elements
    assert(copy.size() == vec.size());
    for(size_t i = 0; i < vec.size(); ++i){
        assert(copy[i] == vec[i]);
    }

    // Ensure deep copy
    copy[1] = 20;
    assert(copy[1] != vec[1]);

    // Test self-assignment
    copy = copy;
    assert(copy.size() == 3);
    assert(copy[0] == 1);

    std::cout << "Copy assignment tests passed!" << std::endl;
}

void test_reserve(){
    CustomCXX::Vector<int> vec;
    vec.reserve(10);
    assert(vec.capacity() >= 10);
    assert(vec.size() == 0);

    // Reserve less than current capacity
    size_t old_capacity = vec.capacity();
    vec.reserve(5);
    assert(vec.capacity() == old_capacity);

    std::cout << "Reserve tests passed!" << std::endl;
}

void test_shrink_to_fit(){
    CustomCXX::Vector<int> vec = {1, 2, 3};
    vec.reserve(10);
    size_t old_capacity = vec.capacity();
    vec.shrink_to_fit();
    assert(vec.capacity() == vec.size());
    assert(vec.capacity() < old_capacity);

    // Ensure no data loss
    for(size_t i = 0; i < vec.size(); ++i){
        assert(vec[i] == i + 1);
    }

    std::cout << "Shrink to fit tests passed!" << std::endl;
}



int main() {
    test_vector();
    return 0;
}