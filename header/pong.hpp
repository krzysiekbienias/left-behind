#pragma once
#include <string>
#include <gtest/gtest_prod.h>


class Pong {
public:
    int m_max_score;
    Pong(int max_score);

    std::string play(int ball_pos, int player_pos);

private:
    int m_player1=0;
    int m_player2=0;
    bool m_player1Turn=true;
    bool hitOrMiss(int ball_pos,int player_pos);
    FRIEND_TEST(Pong,HitOrMiss);

};

