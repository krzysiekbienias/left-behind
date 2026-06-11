#include <gtest/gtest.h>

#include "smallest_number_in_infinite_set.hpp"

TEST(SmallestInfiniteSetTests, PopSmallestReturnsSequentialNumbers) {
    SmallestInfiniteSet set;

    EXPECT_EQ(set.popSmallest(), 1);
    EXPECT_EQ(set.popSmallest(), 2);
    EXPECT_EQ(set.popSmallest(), 3);
}

TEST(SmallestInfiniteSetTests, AddBackThenPopReturnsAddedNumberFirst) {
    SmallestInfiniteSet set;

    EXPECT_EQ(set.popSmallest(), 1);
    EXPECT_EQ(set.popSmallest(), 2);

    set.addBack(1);
    EXPECT_EQ(set.popSmallest(), 1);
    EXPECT_EQ(set.popSmallest(), 3);
}

TEST(SmallestInfiniteSetTests, LeetCodeStyleSequence) {
    SmallestInfiniteSet set;

    EXPECT_EQ(set.popSmallest(), 1);
    EXPECT_EQ(set.popSmallest(), 2);
    set.addBack(1);
    EXPECT_EQ(set.popSmallest(), 1);
    EXPECT_EQ(set.popSmallest(), 3);
    set.addBack(2);
    set.addBack(3);
    EXPECT_EQ(set.popSmallest(), 2);
    EXPECT_EQ(set.popSmallest(), 3);
    EXPECT_EQ(set.popSmallest(), 4);
    EXPECT_EQ(set.popSmallest(), 5);
}

TEST(SmallestInfiniteSetTests, AddBackGreaterOrEqualNextFreshIsIgnored) {
    SmallestInfiniteSet set;

    EXPECT_EQ(set.popSmallest(), 1);
    EXPECT_EQ(set.popSmallest(), 2);

    set.addBack(2);  // equal to nextFresh (3) boundary: 2 < 3, valid
    set.addBack(3);  // num >= nextFresh, ignored
    set.addBack(4);  // ignored

    EXPECT_EQ(set.popSmallest(), 2);
    EXPECT_EQ(set.popSmallest(), 3);
}

TEST(SmallestInfiniteSetTests, MultipleAddedBackNumbersPopInAscendingOrder) {
    SmallestInfiniteSet set;

    for (int i = 1; i <= 5; ++i) {
        EXPECT_EQ(set.popSmallest(), i);
    }

    set.addBack(2);
    set.addBack(4);

    EXPECT_EQ(set.popSmallest(), 2);
    EXPECT_EQ(set.popSmallest(), 4);
    EXPECT_EQ(set.popSmallest(), 6);
}

TEST(SmallestInfiniteSetTests, AddBackSameNumberTwiceIsNoOpDuplicate) {
    SmallestInfiniteSet set;

    EXPECT_EQ(set.popSmallest(), 1);
    set.addBack(1);
    set.addBack(1);

    EXPECT_EQ(set.popSmallest(), 1);
    EXPECT_EQ(set.popSmallest(), 2);
}
