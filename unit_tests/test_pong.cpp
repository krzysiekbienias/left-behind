#include <gtest/gtest.h>

#include <string>
#include "pong.hpp"

TEST(Pong,Constructor) {
    Pong p(4);
    EXPECT_EQ(p.m_max_score,4);
}
//TODO add test for invalid constructor parameter

TEST(Pong,HitOrMiss) {
    Pong p(4);

    EXPECT_TRUE(p.hitOrMiss(50,53));
}

TEST(Pong,TwoHitsPlay) {
    Pong p(2);
    EXPECT_EQ(p.play(50,53),"Player 1 has hit the ball!");
    EXPECT_EQ(p.play(100,97),"Player 2 has hit the ball!");

}



TEST(Pong, LongerGame)
{
    Pong game(2);

    EXPECT_EQ(game.play(50, 53), "Player 1 has hit the ball!");     // Player 1's turn
    EXPECT_EQ(game.play(100, 97), "Player 2 has hit the ball!");    // Player 2's turn
    EXPECT_EQ(game.play(0, 4), "Player 1 has missed the ball!");    // Player 1's turn
    EXPECT_EQ(game.play(25, 25), "Player 2 has hit the ball!");     // Player 2's turn
    EXPECT_EQ(game.play(75, 25), "Player 2 has won the game!");     // Player 1's turn
    EXPECT_EQ(game.play(50, 50), "Game Over!");
}