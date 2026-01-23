#include <string>
#include "pong.hpp"


Pong::Pong(int max_score) : m_max_score(max_score) {
};

bool Pong::hitOrMiss(int ball_pos, int player_pos) {
    return (std::abs(ball_pos - player_pos) <= 3);
}


std::string Pong::play(int ball_pos, int player_pos) {
    //check if we may still play


    if (m_player1 == m_max_score || m_player2 == m_max_score)
        return "Game Over!";
    //first hit player1
    if (m_player1Turn) {
        //bedzie odbijal p1
        if (hitOrMiss(ball_pos, player_pos)) {
            m_player1Turn = false;
            return "Player 1 has hit the ball!";
        }
        if (++m_player2 == m_max_score)return "Player 2 has won the game!";
        m_player1Turn = false;
        return "Player 1 has missed the ball!";
    }

    if (hitOrMiss(ball_pos, player_pos)) {
        m_player1Turn = true;
        return "Player 2 has hit the ball!";
    }
    if (++m_player1 == m_max_score)return "Player 1 has won the game!";
    m_player1Turn = false;
    return "Player 2 has missed the ball!";
}
