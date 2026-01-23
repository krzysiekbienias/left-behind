#pragma once
#include <string>

struct Card {
    int rank;
    char suit;
    static Card parse(std::string token);
};

inline bool operator==(Card const & c1,Card const & c2) {

    return c1.rank==c2.rank && c1.suit==c2.suit;
};

struct PokerHand {
    PokerHand (const char* pokerhand) {}


};

enum class Result { Win, Loss, Tie };

Result compare (const PokerHand &player, const PokerHand &opponent);

enum class HandValues {
    highCard,Pair,TwoPairs,ThreeOfAKind,Straight,Flush,
    FullHouse,FourOfAKind,StraightFlush,RoyalFlush
};


