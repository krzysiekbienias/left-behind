#include <gtest/gtest.h>

#include <random>
#include <unordered_map>

#include "design_hash_map.hpp"

namespace {
// Must match MyHashMap::BUCKETS (private). Keys that differ by a multiple of
// this value land in the same bucket.
constexpr int kBuckets = 10007;
}  // namespace

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
    constexpr int bucket_mate = 1 + kBuckets;

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
    constexpr int bucket_mate = 5 + kBuckets;

    MyHashMap map;
    map.put(5, 50);
    map.put(bucket_mate, 500);

    map.remove(bucket_mate);

    EXPECT_EQ(map.get(5), 50);
    EXPECT_EQ(map.get(bucket_mate), -1);
}

// ---------------------------------------------------------------------------
// Stronger tests
// ---------------------------------------------------------------------------

TEST(MyHashMapTests, PutIntoEmptyBucketInserts) {
    MyHashMap map;

    map.put(7, 70);

    EXPECT_EQ(map.get(7), 70);
}

TEST(MyHashMapTests, ZeroValueIsDistinctFromMissing) {
    MyHashMap map;

    map.put(3, 0);

    EXPECT_EQ(map.get(3), 0);
    EXPECT_EQ(map.get(4), -1);
}

TEST(MyHashMapTests, ZeroAndMaxKeysWork) {
    constexpr int max_key = 1'000'000;

    MyHashMap map;
    map.put(0, 1);
    map.put(max_key, 2);

    EXPECT_EQ(map.get(0), 1);
    EXPECT_EQ(map.get(max_key), 2);
}

TEST(MyHashMapTests, ThreeKeysInOneBucketAllRetrievable) {
    const int a = 9;
    const int b = a + kBuckets;
    const int c = a + 2 * kBuckets;

    MyHashMap map;
    map.put(a, 1);
    map.put(b, 2);
    map.put(c, 3);

    EXPECT_EQ(map.get(a), 1);
    EXPECT_EQ(map.get(b), 2);
    EXPECT_EQ(map.get(c), 3);
}

// Inserting a new key into a bucket that already holds >= 2 other keys must
// add it exactly once. Catches inserting inside the search loop (duplicates):
// after remove() the key must be really gone.
TEST(MyHashMapTests, PutNewKeyIntoBucketWithTwoEntriesAddsItOnce) {
    const int a = 9;
    const int b = a + kBuckets;
    const int c = a + 2 * kBuckets;

    MyHashMap map;
    map.put(a, 1);
    map.put(b, 2);
    map.put(c, 3);

    map.remove(c);

    EXPECT_EQ(map.get(c), -1);
    EXPECT_EQ(map.get(a), 1);
    EXPECT_EQ(map.get(b), 2);
}

TEST(MyHashMapTests, PutExistingKeyDoesNotDuplicate) {
    MyHashMap map;

    map.put(1, 10);
    map.put(1, 20);
    map.put(1, 30);

    map.remove(1);

    EXPECT_EQ(map.get(1), -1);
}

TEST(MyHashMapTests, UpdateKeyInCollidingBucketOnlyChangesThatKey) {
    const int a = 4;
    const int b = a + kBuckets;
    const int c = a + 2 * kBuckets;

    MyHashMap map;
    map.put(a, 1);
    map.put(b, 2);
    map.put(c, 3);

    map.put(b, 222);

    EXPECT_EQ(map.get(a), 1);
    EXPECT_EQ(map.get(b), 222);
    EXPECT_EQ(map.get(c), 3);

    map.remove(b);
    EXPECT_EQ(map.get(b), -1);
}

TEST(MyHashMapTests, RemoveMiddleOfCollidingBucket) {
    const int a = 11;
    const int b = a + kBuckets;
    const int c = a + 2 * kBuckets;

    MyHashMap map;
    map.put(a, 1);
    map.put(b, 2);
    map.put(c, 3);

    map.remove(b);

    EXPECT_EQ(map.get(a), 1);
    EXPECT_EQ(map.get(b), -1);
    EXPECT_EQ(map.get(c), 3);
}

TEST(MyHashMapTests, RemoveTwiceIsSafe) {
    MyHashMap map;

    map.put(8, 80);
    map.remove(8);
    map.remove(8);

    EXPECT_EQ(map.get(8), -1);
}

TEST(MyHashMapTests, RemoveFromEmptyMapIsSafe) {
    MyHashMap map;

    map.remove(123);

    EXPECT_EQ(map.get(123), -1);
}

TEST(MyHashMapTests, PutAfterRemoveRestoresKey) {
    MyHashMap map;

    map.put(6, 60);
    map.remove(6);
    map.put(6, 61);

    EXPECT_EQ(map.get(6), 61);
}

TEST(MyHashMapTests, ManyDistinctKeysAllRetrievable) {
    MyHashMap map;
    constexpr int n = 50'000;  // far more than kBuckets -> many collisions

    for (int i = 0; i < n; ++i) {
        map.put(i, i * 2 + 1);
    }

    for (int i = 0; i < n; ++i) {
        ASSERT_EQ(map.get(i), i * 2 + 1) << "key=" << i;
    }
    EXPECT_EQ(map.get(n), -1);
}

TEST(MyHashMapTests, RemoveEveryOtherKeyOfMany) {
    MyHashMap map;
    constexpr int n = 30'000;

    for (int i = 0; i < n; ++i) {
        map.put(i, i);
    }
    for (int i = 0; i < n; i += 2) {
        map.remove(i);
    }

    for (int i = 0; i < n; ++i) {
        const int expected = (i % 2 == 0) ? -1 : i;
        ASSERT_EQ(map.get(i), expected) << "key=" << i;
    }
}

// Randomized differential test against std::unordered_map. Keys are drawn from
// a small set of residues times kBuckets so that heavy bucket collisions occur.
TEST(MyHashMapTests, RandomOperationsMatchUnorderedMap) {
    std::mt19937 rng(12345);
    std::uniform_int_distribution<int> op_dist(0, 2);
    std::uniform_int_distribution<int> residue_dist(0, 4);
    std::uniform_int_distribution<int> mult_dist(0, 8);
    std::uniform_int_distribution<int> value_dist(0, 1'000'000);

    MyHashMap map;
    std::unordered_map<int, int> reference;

    for (int step = 0; step < 20'000; ++step) {
        const int key = residue_dist(rng) + mult_dist(rng) * kBuckets;

        switch (op_dist(rng)) {
            case 0: {
                const int value = value_dist(rng);
                map.put(key, value);
                reference[key] = value;
                break;
            }
            case 1: {
                map.remove(key);
                reference.erase(key);
                break;
            }
            default: {
                const auto it = reference.find(key);
                const int expected = it == reference.end() ? -1 : it->second;
                ASSERT_EQ(map.get(key), expected) << "step=" << step << " key=" << key;
                break;
            }
        }
    }

    for (int r = 0; r < 5; ++r) {
        for (int m = 0; m < 9; ++m) {
            const int key = r + m * kBuckets;
            const auto it = reference.find(key);
            const int expected = it == reference.end() ? -1 : it->second;
            EXPECT_EQ(map.get(key), expected) << "key=" << key;
        }
    }
}
