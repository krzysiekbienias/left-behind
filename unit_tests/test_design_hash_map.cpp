#include <gtest/gtest.h>

#include "design_hash_map.hpp"

TEST(MyHashMapTests, GetMissingReturnsMinusOne) {
    MyHashMap map;

    EXPECT_EQ(map.get(42), -1);
}

TEST(MyHashMapTests, PutThenGetReturnsValue) {
    MyHashMap map;

    map.put(1, 100);
    map.put(2, 200);

    EXPECT_EQ(map.get(1), 100);
    EXPECT_EQ(map.get(2), 200);
}

TEST(MyHashMapTests, PutUpdatesExistingKey) {
    MyHashMap map;

    map.put(1, 10);
    map.put(1, 99);

    EXPECT_EQ(map.get(1), 99);
}

TEST(MyHashMapTests, RemoveExistingKey) {
    MyHashMap map;

    map.put(1, 10);
    map.put(2, 20);

    map.remove(1);

    EXPECT_EQ(map.get(1), -1);
    EXPECT_EQ(map.get(2), 20);
}

TEST(MyHashMapTests, RemoveMissingKeyIsNoOp) {
    MyHashMap map;

    map.put(1, 10);
    map.remove(999);

    EXPECT_EQ(map.get(1), 10);
}

TEST(MyHashMapTests, KeysInSameBucketDoNotCollide) {
    // m_n = 10009; keys differing by m_n land in the same bucket.
    constexpr int bucket_mate = 1 + (10 * 10 * 10 + 9);

    MyHashMap map;
    map.put(1, 111);
    map.put(bucket_mate, 222);

    EXPECT_EQ(map.get(1), 111);
    EXPECT_EQ(map.get(bucket_mate), 222);

    map.remove(1);
    EXPECT_EQ(map.get(1), -1);
    EXPECT_EQ(map.get(bucket_mate), 222);
}

TEST(MyHashMapTests, RemoveOneOfCollidingBucketsLeavesOther) {
    constexpr int bucket_mate = 5 + (10 * 10 * 10 + 9);

    MyHashMap map;
    map.put(5, 50);
    map.put(bucket_mate, 500);

    map.remove(bucket_mate);

    EXPECT_EQ(map.get(5), 50);
    EXPECT_EQ(map.get(bucket_mate), -1);
}