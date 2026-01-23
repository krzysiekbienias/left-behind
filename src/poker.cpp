#include <string>
#include <vector>
#include <unordered_map>
#include "poker.hpp"


Card Card::parse(std::string token) {
    static std::unordered_map<char, int> rankMap = {
        {'1', 1},
        {'2', 2},
        {'3', 3},
        {'4', 4},
        {'5', 5},
        {'6', 6},
        {'7', 7},
        {'8', 8},
        {'9', 9},
        {'T',10},
        {'J',11},
        {'Q',12},
        {'K',13},
        {'A',14},

    };

    return {rankMap[token[0]], token[1]};
}


