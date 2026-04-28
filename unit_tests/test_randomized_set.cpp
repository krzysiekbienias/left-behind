#include <gtest/gtest.h>
#include <unordered_set>
#include "randomized_set.hpp" // Assuming this is the header name

// Test basic insertion and uniqueness constraints
TEST(RandomizedSetTest, InsertOperations) {
    RandomizedSet rs;

    // First insertion should succeed
    EXPECT_TRUE(rs.insert(10));

    // Duplicate insertion should fail
    EXPECT_FALSE(rs.insert(10));

    // Inserting a different value should succeed
    EXPECT_TRUE(rs.insert(20));
}

// Test removal logic and edge cases
TEST(RandomizedSetTest, RemoveOperations) {
    RandomizedSet rs;

    rs.insert(1);
    rs.insert(2);

    // Removing existing element
    EXPECT_TRUE(rs.remove(1));

    // Removing same element again should fail
    EXPECT_FALSE(rs.remove(1));

    // Removing non-existent element
    EXPECT_FALSE(rs.remove(100));

    // Ensure set still functions after removal
    EXPECT_TRUE(rs.insert(1));
}

// Test the getRandom functionality
TEST(RandomizedSetTest, GetRandomValidity) {
    RandomizedSet rs;
    rs.insert(10);
    rs.insert(20);
    rs.insert(30);

    // Over multiple calls, getRandom should only return inserted elements
    for(int i = 0; i < 10; ++i) {
        int val = rs.getRandom();
        EXPECT_TRUE(val == 10 || val == 20 || val == 30);
    }
}

// Test sequence of operations (Mixed Scenario)
TEST(RandomizedSetTest, MixedOperations) {
    RandomizedSet rs;

    EXPECT_TRUE(rs.insert(1));   // {1}
    EXPECT_FALSE(rs.remove(2));  // {1}
    EXPECT_TRUE(rs.insert(2));   // {1, 2}

    int val = rs.getRandom();
    EXPECT_TRUE(val == 1 || val == 2);

    EXPECT_TRUE(rs.remove(1));   // {2}
    EXPECT_FALSE(rs.insert(2));  // {2}

    // Only one element left, getRandom must return 2
    EXPECT_EQ(rs.getRandom(), 2);
}

// Test behavior with a larger dataset to ensure no index corruption
TEST(RandomizedSetTest, LargeScaleStress) {
    RandomizedSet rs;
    const int count = 100;

    for (int i = 0; i < count; ++i) {
        rs.insert(i);
    }

    for (int i = 0; i < count; ++i) {
        int val = rs.getRandom();
        EXPECT_GE(val, 0);
        EXPECT_LT(val, count);
    }

    for (int i = 0; i < count; i += 2) {
        EXPECT_TRUE(rs.remove(i));
    }

    // After removing all evens, getRandom should only yield odds
    for (int i = 0; i < 10; ++i) {
        EXPECT_EQ(rs.getRandom() % 2, 1);
    }
}