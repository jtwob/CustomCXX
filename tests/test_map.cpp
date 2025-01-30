#include "Map.h"
#include <gtest/gtest.h>
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

TEST(MapTest, TestBasicOperations) {
    CustomCXX::Map<int, std::string> map;

    // Insert and access elements
    map[1] = "one";
    map[2] = "two";

    EXPECT_EQ(map[1], "one");
    EXPECT_EQ(map[2], "two");

    // Check size
    EXPECT_EQ(map.size(), 2);

    // Overwrite a value
    map[1] = "uno";
    EXPECT_EQ(map[1], "uno");
}

TEST(MapTest, TestEraseAndContains) {
    CustomCXX::Map<int, std::string> map;

    map[1] = "one";
    map[2] = "two";
    map[3] = "three";

    // Erase an element
    map.erase(2);
    EXPECT_TRUE(!map.contains(2));

    // Check remaining elements
    EXPECT_TRUE(map.contains(1));
    EXPECT_TRUE(map.contains(3));
}

TEST(MapTest, TestOperatorBrackets) {
    CustomCXX::Map<int, std::string> map;
    map[1] = "one";
    EXPECT_EQ(map[1], "one");
}

TEST(MapTest, TestEraseSingleKey) {
    CustomCXX::Map<int, std::string> map;

    map[1] = "one";
    map[2] = "two";

    EXPECT_TRUE(map.contains(1));
    map.erase(1);
    EXPECT_TRUE(!map.contains(1)); // Should pass
    EXPECT_TRUE(map.contains(2));  // Other keys should remain intact
}

TEST(MapTest, TestContainsKeyNotPresent) {
    CustomCXX::Map<int, std::string> map;

    map[1] = "one";

    EXPECT_TRUE(!map.contains(2)); // Should pass
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

// Run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}