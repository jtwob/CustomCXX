#include "Map.h"
#include <gtest/gtest.h>
#include <iostream>
#include <string>

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

TEST(MapTest, TestRehashing) {
    CustomCXX::Map<int, std::string> map(4); // Small initial bucket count
    for (int i = 0; i < 10; ++i) {
        map[i] = "value" + std::to_string(i);
    }

    EXPECT_EQ(map.size(), 10); // Ensure all elements are present
}

TEST(MapTest, TestInsertOrAssign) {
    CustomCXX::Map<int, std::string> map;

    map.insert_or_assign(1, "one");
    EXPECT_TRUE(map.contains(1)); 
    EXPECT_EQ(map[1], "one");

    map.insert_or_assign(1, "uno"); // Update existing key
    EXPECT_EQ(map[1], "uno");
}

TEST(MapTest, TestKeys) {
    CustomCXX::Map<int, std::string> map;

    map[1] = "one";
    map[2] = "two";
    map[3] = "three";

    auto key_list = map.keys();
    EXPECT_EQ(key_list.size(), 3);
    EXPECT_TRUE(key_list[0] == 1 || key_list[1] == 1 || key_list[2] == 1);
    EXPECT_TRUE(key_list[0] == 2 || key_list[1] == 2 || key_list[2] == 2);
    EXPECT_TRUE(key_list[0] == 3 || key_list[1] == 3 || key_list[2] == 3);
}

// Run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}