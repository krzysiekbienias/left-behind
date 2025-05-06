// header/CSVParser.hpp
#pragma once
#include "market_data_parser.hpp"
#include <string>
#include <vector>

class CSVParser : public IMarketDataParser {
public:
    MarketTick parse(const std::string& line) const override;  // Just a declaration here
    std::vector<MarketTick> parseStream(std::istream & input) const override;
};
