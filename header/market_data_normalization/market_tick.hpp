#pragma once
#include <string>

struct MarketTick {
    std::string timestamp;
    std::string symbol;
    double bid;
    double ask;
};
