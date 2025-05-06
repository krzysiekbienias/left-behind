#pragma once
#include "market_data_parser.hpp"
#include <vector>

class JSONParser : public IMarketDataParser {
public:
    //full inline definition
    MarketTick parse(const std::string& line) const override {
        throw std::logic_error("parse() not used for JSON file array mode");
    }
    

    std::vector<MarketTick> parseStream(std::istream& input) const override;
};
