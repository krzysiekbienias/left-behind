#include "moving_average.hpp"
#include <gtest/gtest.h>
#include <stdexcept>

// Test constructor and getSize
TEST(MovingAverageTest, ConstructorAndGetSize) {
    MovingAverage ma(3);
    EXPECT_EQ(ma.getSize(), 3);
}

// Test setSize with valid input
TEST(MovingAverageTest, SetSizeValid) {
    MovingAverage ma(3);
    ma.setSize(5);
    EXPECT_EQ(ma.getSize(), 5);
}

// Test setSize with invalid input (zero or negative)
TEST(MovingAverageTest, SetSizeInvalid) {
    MovingAverage ma(3);
    EXPECT_THROW(ma.setSize(0), std::out_of_range);
    EXPECT_THROW(ma.setSize(-2), std::out_of_range);
}

// Test next() with fewer elements than window size
TEST(MovingAverageTest, NextFewerThanWindowSize) {
    MovingAverage ma(3);
    EXPECT_FLOAT_EQ(ma.next(10), 10.0f);
    EXPECT_FLOAT_EQ(ma.next(20), 15.0f);
}

// Test next() with more elements than window size
TEST(MovingAverageTest, NextExceedingWindowSize) {
    MovingAverage ma(3);
    ma.next(10);  // [10]
    ma.next(20);  // [10, 20]
    ma.next(30);  // [10, 20, 30]
    EXPECT_FLOAT_EQ(ma.next(40), (20 + 30 + 40) / 3.0f);  // [20, 30, 40]
    EXPECT_FLOAT_EQ(ma.next(50), (30 + 40 + 50) / 3.0f);  // [30, 40, 50]
}
