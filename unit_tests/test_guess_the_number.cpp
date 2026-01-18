#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

#include "complex_numbers.hpp"
#include "guess_the_number.hpp"

TEST(GuessTheNumber, TrueForCorrect) {
    Guesser guesser(10,2);
    EXPECT_TRUE(guesser.guess(10));
}

TEST(GuessTheNumber, MultipleCorrectGuesses) {
    Guesser guesser(10,2);
    for (int i = 0; i < 10; ++i) {
        EXPECT_TRUE(guesser.guess(10));
    }
}

TEST(GuessTheNumber, IncorrectGuess) {
    Guesser guesser(10,2);
    EXPECT_FALSE(guesser.guess(1));
}

TEST(GuessTheNumber, RunOutOfLives) {
    Guesser guesser(10,2);
    guesser.guess(1);
    guesser.guess(2);
    EXPECT_THROW(guesser.guess(1),std::exception);
}
