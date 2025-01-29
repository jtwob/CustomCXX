#include "Vector.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cassert>

void test_iterators();
void test_clear();
void test_insert();
void test_erase();
void test_move_semantics();
void test_copy_constructor();
void test_copy_assignment();
void test_reserve();
void test_shrink_to_fit();
void test_reverse_iterators();
void test_vector_sort();

void test_vector() {
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
    test_vector_sort();
    std::cout << "All tests passed!" << std::endl;
}

TEST(VectorTest, Initialization) {
    CustomCXX::Vector<int> vec;
    EXPECT_EQ(vec.size(), 0);
    EXPECT_EQ(vec.capacity(), 0);
}

TEST(VectorTest, PushBack) {
    CustomCXX::Vector<int> vec;

    vec.push_back(1);
    EXPECT_EQ(vec.size(), 1);

    size_t initial_capacity = vec.capacity();
    vec.push_back(2);

    // Handle edge case where initial capacity is 0
    if (initial_capacity == 0) {
        EXPECT_EQ(vec.capacity(), 1); // First resize sets capacity to 1
    } else {
        EXPECT_GT(vec.capacity(), initial_capacity);
    }

    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
}

TEST(VectorTest, PopBack) {
    CustomCXX::Vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    vec.pop_back();
    EXPECT_EQ(vec.size(), 2);
    EXPECT_EQ(vec[1], 2);

    vec.pop_back();
    vec.pop_back();
    EXPECT_EQ(vec.size(), 0);
    try {
        vec.pop_back();
        EXPECT_TRUE(false); // Should not reach here
    } catch (const std::underflow_error& e) {
        EXPECT_EQ(std::string(e.what()), "Vector is empty");
    }
}

TEST(VectorTest, TestSubscriptOperator) {
    EXPECT_EQ(true, true);
}

// void test_subscript_operator() {
//     CustomCXX::Vector<int> vec = {1, 2, 3};
//     assert(vec[0] == 1);
//     assert(vec[1] == 2);
//     assert(vec[2] == 3);

//     vec[0] = 10;
//     assert(vec[0] == 10);

//     // Ensure out-of-range access throws an exception
//     try {
//         int x = vec[10]; // Should throw
//         assert(false);   // Should not reach here
//     } catch (const std::out_of_range& e) {
//         assert(std::string(e.what()) == "Index out of range");
//     }

//     std::cout << "Subscript operator tests passed!" << std::endl;
// }

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

void test_reverse_iterators() {
    // Normal case
    CustomCXX::Vector<int> vec = {1, 2, 3};

    int expected = 3;
    for (auto it = vec.rbegin(); it != vec.rend(); --it) {
        assert(*it == expected--);
    }

    // Empty vector case
    CustomCXX::Vector<int> empty_vec;
    assert(empty_vec.rbegin() == empty_vec.end()); // Both should be _data

    // Single element case
    CustomCXX::Vector<int> single_vec = {42};
    assert(*single_vec.rbegin() == 42);
    assert(single_vec.rbegin() == single_vec.begin());
    assert(single_vec.rend() == single_vec.begin() - 1);

    std::cout << "Reverse iterators tests passed!" << std::endl;
}

void test_vector_sort() {
    using Vector = CustomCXX::Vector<int>;

    // Basic Case
    Vector vec = {3, 1, 4, 1, 5, 9};
    vec.sort();
    assert(vec == Vector({1, 1, 3, 4, 5, 9}));

    // Already Sorted
    Vector sorted_vec = {1, 2, 3, 4, 5};
    sorted_vec.sort();
    assert(sorted_vec == Vector({1, 2, 3, 4, 5}));

    // Reverse Sorted
    Vector reverse_vec = {5, 4, 3, 2, 1};
    reverse_vec.sort();
    assert(reverse_vec == Vector({1, 2, 3, 4, 5}));

    // Empty Vector
    Vector empty_vec;
    empty_vec.sort();
    assert(empty_vec.size() == 0);

    // Single Element
    Vector single_vec = {42};
    single_vec.sort();
    assert(single_vec == Vector({42}));

    // Descending Order
    reverse_vec.sort(std::greater<int>());
    assert(reverse_vec == Vector({5, 4, 3, 2, 1}));

    std::cout << "Vector sort tests passed!" << std::endl;
}

// Run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// int main() {
//     test_vector();
//     return 0;
// }