#include "List.h"
#include <gtest/gtest.h>
#include <iostream>

TEST(ListTest, TestBasicList) {
    CustomCXX::List<int> list;

    // Test push_front and push_back
    list.push_front(1);
    list.push_back(2);
    list.push_back(3);
    EXPECT_EQ(list.size(), 3);
    EXPECT_EQ(list.front(), 1);
    EXPECT_EQ(list.back(), 3);

    // Test pop_front and pop_back
    list.pop_front();
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 2);

    list.pop_back();
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.back(), 2);

    // Test clear
    list.clear();
    EXPECT_TRUE(list.empty());
}

TEST(ListTest, TestInsert) {
    CustomCXX::List<int> list;

    // Insert into an empty list
    list.insert(0, 1);
    EXPECT_EQ(list.size(), 1);
    EXPECT_EQ(list.front(), 1);

    // Insert at the beginning
    list.insert(0, 0);
    EXPECT_EQ(list.front(), 0);

    // Insert in the middle
    list.insert(1, 2);
    EXPECT_EQ(list.at(1), 2);

    // Insert at the end
    list.insert(3, 3);
    EXPECT_EQ(list.back(), 3);
}

TEST(ListTest, TestErase) {
    CustomCXX::List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Erase from the beginning
    list.erase(0);
    EXPECT_EQ(list.front(), 2);
    EXPECT_EQ(list.size(), 2);

    // Erase from the middle
    list.push_back(4);
    list.erase(1); // Should remove the element "3"
    EXPECT_EQ(list.at(1), 4);

    // Erase from the end
    list.pop_back();
    EXPECT_EQ(list.back(), 2);
    EXPECT_EQ(list.size(), 1);
}

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

void test_list_sort() {
    using List = CustomCXX::List<int>;

    // Basic Case
    List list = {3, 1, 4, 1, 5, 9};
    list.sort();
    assert(list == List({1, 1, 3, 4, 5, 9}));

    // Already Sorted
    List sorted_list = {1, 2, 3, 4, 5};
    sorted_list.sort();
    assert(sorted_list == List({1, 2, 3, 4, 5}));

    // Reverse Sorted
    List reverse_list = {5, 4, 3, 2, 1};
    reverse_list.sort();
    assert(reverse_list == List({1, 2, 3, 4, 5}));

    // Empty List
    List empty_list;
    empty_list.sort();
    assert(empty_list.size() == 0);

    // Single Element
    List single_list = {42};
    single_list.sort();
    assert(single_list == List({42}));

    // Descending Order
    reverse_list.sort(std::greater<int>());
    assert(reverse_list == List({5, 4, 3, 2, 1}));

    std::cout << "List sort tests passed!" << std::endl;
}

// Run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}