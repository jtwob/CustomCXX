#include "Vector.h"
#include <gtest/gtest.h>
#include <iostream>
#include <cassert>

void test_reverse_iterators();
void test_vector_sort();

void test_vector() {
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
    
    // Underflow check
    try {
        vec.pop_back();
        EXPECT_TRUE(false); // Should not reach here
    } catch (const std::underflow_error& e) {
        EXPECT_EQ(std::string(e.what()), "Vector is empty");
    }
}

TEST(VectorTest, TestSubscriptOperator) {
    CustomCXX::Vector<int> vec = {1, 2, 3};
    EXPECT_EQ(vec[0], 1);
    EXPECT_EQ(vec[1], 2);
    EXPECT_EQ(vec[2], 3);

    vec[0] = 10;
    EXPECT_EQ(vec[0], 10);
    
    // Ensure out-of-range access throws an exception
    try {
        int x = vec[10]; // Should throw
        EXPECT_TRUE(false);   // Should not reach here
    } catch (const std::out_of_range& e) {
        EXPECT_EQ(std::string(e.what()), "Index out of range");
    }
}

TEST(VectorTest, TestIterators) {
    CustomCXX::Vector<int> vec = {1, 2, 3};
    int sum = 0;

    for (auto it = vec.begin(); it != vec.end(); ++it) {
        sum += *it;
    }

    EXPECT_EQ(sum, 6);
}

TEST(VectorTest, TestClear) {
    CustomCXX::Vector<int> vec = {1, 2, 3, 4, 5};
    vec.clear();
    EXPECT_EQ(vec.size(), 0);
    EXPECT_GT(vec.capacity(), 0); // Capacity should remain unchanged

    // Ensure accessing elements throws an error
    try {
        int x = vec[0];
        EXPECT_TRUE(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        EXPECT_EQ(std::string(e.what()),"Index out of range");
    }
}

TEST(VectorTest, TestInsert) {
    CustomCXX::Vector<int> vec = {1, 2, 4, 5};

    // Insert in the middle
    vec.insert(2, 3);
    EXPECT_EQ(vec[2], 3);
    EXPECT_EQ(vec[3], 4);
    EXPECT_EQ(vec.size(), 5);

    // Insert at the beginning
    vec.insert(0, 0);
    EXPECT_EQ(vec[0], 0);
    EXPECT_EQ(vec.size(), 6);

    // Insert at the end
    vec.insert(vec.size(), 6);
    EXPECT_EQ(vec[vec.size() - 1], 6);

    // Handle invalid indices
    try {
        vec.insert(10, 99);
        EXPECT_TRUE(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        EXPECT_EQ(std::string(e.what()), "Index out of range");
    }
}

TEST(VectorTest, TestErase) {
    CustomCXX::Vector<int> vec = {1, 2, 3, 4, 5};

    // Erase middle element
    vec.erase(2);
    EXPECT_EQ(vec[2], 4);
    EXPECT_EQ(vec.size(), 4);

    // Erase first element
    vec.erase(0);
    EXPECT_EQ(vec[0], 2);
    EXPECT_EQ(vec.size(), 3);

    // Erase last element
    vec.erase(vec.size() - 1);
    EXPECT_EQ(vec.size(), 2);

    // Handle invalid indices
    try {
        vec.erase(10);
        EXPECT_TRUE(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        EXPECT_EQ(std::string(e.what()),"Index out of range");
    }

}

TEST(VectorTest, TestMoveSemantics) {
    CustomCXX::Vector<int> vec1 = {1, 2, 3};
    CustomCXX::Vector<int> vec2 = std::move(vec1);

    // Ensure vec2 has taken ownership of vec1's data
    EXPECT_EQ(vec2.size(), 3);
    EXPECT_EQ(vec2[0], 1);

    // Ensure vec1 is empty
    EXPECT_EQ(vec1.size(), 0);
    try {
        int x = vec1[0];
        EXPECT_TRUE(false); // Should not reach here
    } catch (const std::out_of_range& e) {
        EXPECT_EQ(std::string(e.what()), "Index out of range");
    }
}

TEST(VectorTest, TestCopyConstructor) {
    CustomCXX::Vector<int> vec = {1, 2, 3};
    CustomCXX::Vector<int> copy(vec);

    // Ensure copy has the same elements;
    EXPECT_EQ(copy.size(), vec.size());
    for(size_t i = 0; i < vec.size(); ++i){
        EXPECT_EQ(copy[i], vec[i]);
    }

    // Ensure deep copy
    copy[0] = 10;
    EXPECT_NE(copy[0], vec[0]);
}

TEST(VectorTest, TestCopyAssignment) {
    CustomCXX::Vector<int> vec = {1, 2, 3};
    CustomCXX::Vector<int> copy;
    copy = vec;

    // Ensure copy has the same elements
    EXPECT_EQ(copy.size(), vec.size());
    for(size_t i = 0; i < vec.size(); ++i){
        EXPECT_EQ(copy[i], vec[i]);
    }

    // Ensure deep copy
    copy[1] = 20;
    EXPECT_NE(copy[1], vec[1]);

    // Test self-assignment
    copy = copy;
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy[0], 1);
}

TEST(VectorTest, TestReserve){
    CustomCXX::Vector<int> vec;
    vec.reserve(10);
    EXPECT_GE(vec.capacity(), 10);
    EXPECT_EQ(vec.size(), 0);

    // Reserve less than current capacity
    size_t old_capacity = vec.capacity();
    vec.reserve(5);
    EXPECT_EQ(vec.capacity(), old_capacity);
}

TEST(VectorTest, TestShrinkToFit) {
    CustomCXX::Vector<int> vec = {1, 2, 3};
    vec.reserve(10);
    size_t old_capacity = vec.capacity();
    vec.shrink_to_fit();
    EXPECT_EQ(vec.capacity(), vec.size());
    EXPECT_LT(vec.capacity(),old_capacity);

    // Ensure no data loss
    for(size_t i = 0; i < vec.size(); ++i){
        EXPECT_EQ(vec[i], i + 1);
    }
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