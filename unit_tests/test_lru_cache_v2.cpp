#include <gtest/gtest.h>

#include "lru_cache_v2.hpp"

TEST(LRUCacheV2Tests, GetMissingReturnsMinusOne) {
    LRUCacheV2 cache(2);

    EXPECT_EQ(cache.get(42), -1);
    EXPECT_EQ(cache.get(-7), -1);
}

TEST(LRUCacheV2Tests, PutThenGetReturnsValue) {
    LRUCacheV2 cache(2);

    cache.put(1, 100);
    cache.put(2, 200);

    EXPECT_EQ(cache.get(1), 100);
    EXPECT_EQ(cache.get(2), 200);
}

TEST(LRUCacheV2Tests, EvictsLeastRecentlyUsedOnCapacityOverflow) {
    LRUCacheV2 cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);

    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(2), 20);
    EXPECT_EQ(cache.get(3), 30);
}

TEST(LRUCacheV2Tests, GetRefreshesRecency) {
    LRUCacheV2 cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    EXPECT_EQ(cache.get(1), 10);
    cache.put(3, 30);

    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(1), 10);
    EXPECT_EQ(cache.get(3), 30);
}

TEST(LRUCacheV2Tests, UpdatingExistingKeyRefreshesRecencyAndValue) {
    LRUCacheV2 cache(2);

    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(1, 111);
    cache.put(3, 30);

    EXPECT_EQ(cache.get(1), 111);
    EXPECT_EQ(cache.get(2), -1);
    EXPECT_EQ(cache.get(3), 30);
}

TEST(LRUCacheV2Tests, CapacityOneKeepsOnlyMostRecent) {
    LRUCacheV2 cache(1);

    cache.put(1, 10);
    EXPECT_EQ(cache.get(1), 10);

    cache.put(2, 20);
    EXPECT_EQ(cache.get(1), -1);
    EXPECT_EQ(cache.get(2), 20);
}

TEST(LRUCacheV2Tests, NonPositiveCapacityStoresNothing) {
    LRUCacheV2 zero_cache(0);
    zero_cache.put(1, 10);
    EXPECT_EQ(zero_cache.get(1), -1);

    LRUCacheV2 negative_cache(-2);
    negative_cache.put(1, 10);
    EXPECT_EQ(negative_cache.get(1), -1);
}
