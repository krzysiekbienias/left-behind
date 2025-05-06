#pragma once
#include "market_tick.hpp"
#include <string>
#include <vector>

//it is abstrac class
class IMarketDataParser {
public:
    virtual MarketTick parse(const std::string& line) const = 0;
    virtual std::vector<MarketTick> parseStream(std::istream & input) const=0;
    virtual ~IMarketDataParser() = default;
};
