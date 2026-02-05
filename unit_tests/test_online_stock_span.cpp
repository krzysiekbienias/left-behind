#include "online_stock_span.hpp"
#include <gtest/gtest.h>

TEST(StockSpannerTest, SingleDayBaseline) {
    StockSpanner sp;

    EXPECT_EQ(sp.next(100), 1);
}

TEST(StockSpannerTest, StrictlyIncreasingPrices) {
    StockSpanner sp;

    EXPECT_EQ(sp.next(10), 1);
    EXPECT_EQ(sp.next(20), 2);
    EXPECT_EQ(sp.next(30), 3);
    EXPECT_EQ(sp.next(40), 4);
}

TEST(StockSpannerTest, StrictlyDecreasingPrices) {
    StockSpanner sp;

    EXPECT_EQ(sp.next(40), 1);
    EXPECT_EQ(sp.next(30), 1);
    EXPECT_EQ(sp.next(20), 1);
    EXPECT_EQ(sp.next(10), 1);
}

TEST(StockSpannerTest, MixedExampleFromProblemStatement) {
    StockSpanner sp;

    EXPECT_EQ(sp.next(7), 1);
    EXPECT_EQ(sp.next(2), 1);
    EXPECT_EQ(sp.next(1), 1);
    EXPECT_EQ(sp.next(2), 3);
}

TEST(StockSpannerTest, EqualPricesAreIncludedInSpan) {
    StockSpanner sp;

    EXPECT_EQ(sp.next(5), 1);
    EXPECT_EQ(sp.next(5), 2);
    EXPECT_EQ(sp.next(5), 3);
}