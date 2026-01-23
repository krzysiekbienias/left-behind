#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <vector>

#include "guess_the_number.hpp"
#include "poker.hpp"
#include "gmock/gmock.h"


using ::testing::ElementsAre;

TEST(Poker, ParseToken) {
    Card res=Card::parse("2H");
    //additional () required
    EXPECT_EQ(res,(Card{2,'H'}));
}

