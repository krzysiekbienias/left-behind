#include <gtest/gtest.h>

#include "seat_reservation_manager.hpp"

TEST(SeatManagerTests, FirstReserveReturnsSeatOne) {
    SeatManager manager(5);

    EXPECT_EQ(manager.reserve(), 1);
}

TEST(SeatManagerTests, SequentialReservesReturnIncreasingSeats) {
    SeatManager manager(5);

    EXPECT_EQ(manager.reserve(), 1);
    EXPECT_EQ(manager.reserve(), 2);
    EXPECT_EQ(manager.reserve(), 3);
}

TEST(SeatManagerTests, UnreserveThenReserveReturnsLowestAvailableSeat) {
    SeatManager manager(5);

    EXPECT_EQ(manager.reserve(), 1);
    EXPECT_EQ(manager.reserve(), 2);
    manager.unreserve(2);

    EXPECT_EQ(manager.reserve(), 2);
}

TEST(SeatManagerTests, PrefersReleasedSeatOverNextFreshSeat) {
    SeatManager manager(5);

    EXPECT_EQ(manager.reserve(), 1);
    EXPECT_EQ(manager.reserve(), 2);
    EXPECT_EQ(manager.reserve(), 3);
    manager.unreserve(2);

    EXPECT_EQ(manager.reserve(), 2);
    EXPECT_EQ(manager.reserve(), 4);
}

TEST(SeatManagerTests, MultipleUnreservedSeatsReturnSmallestFirst) {
    SeatManager manager(5);

    EXPECT_EQ(manager.reserve(), 1);
    EXPECT_EQ(manager.reserve(), 2);
    EXPECT_EQ(manager.reserve(), 3);

    manager.unreserve(3);
    manager.unreserve(1);

    EXPECT_EQ(manager.reserve(), 1);
    EXPECT_EQ(manager.reserve(), 3);
    EXPECT_EQ(manager.reserve(), 4);
}

TEST(SeatManagerTests, LeetCodeStyleSequence) {
    SeatManager manager(5);

    EXPECT_EQ(manager.reserve(), 1);
    EXPECT_EQ(manager.reserve(), 2);
    manager.unreserve(2);
    EXPECT_EQ(manager.reserve(), 2);
    manager.unreserve(1);
    EXPECT_EQ(manager.reserve(), 1);
    EXPECT_EQ(manager.reserve(), 3);
    EXPECT_EQ(manager.reserve(), 4);
    EXPECT_EQ(manager.reserve(), 5);
}

TEST(SeatManagerTests, ReUnreserveSameSeatCanBeReservedAgain) {
    SeatManager manager(3);

    EXPECT_EQ(manager.reserve(), 1);
    manager.unreserve(1);
    EXPECT_EQ(manager.reserve(), 1);
}
