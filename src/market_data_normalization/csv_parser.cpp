#include "market_data_normalization/csv_parser.hpp"
#include "market_data_normalization/market_tick.hpp"
#include <sstream>
#include <string>
#include <iostream>

MarketTick CSVParser::parse(const std::string& line)const {
    std::stringstream ss(line);
    std::string timeStamp, symbol,bid,ask;
    
    std::getline(ss, timeStamp, ',');
    std::getline(ss, symbol, ',');
    std::getline(ss, bid, ',');
    std::getline(ss, ask, ',');
    
    return MarketTick{timeStamp,
        symbol,
        std::stod(bid), //string to double
        std::stod(ask)
    };
}

std::vector<MarketTick> CSVParser::parseStream(std::istream& input) const {
    std::vector<MarketTick> ticks;
    std::string line;

    while (std::getline(input, line)) {
        if (line.empty()) continue;

        try {
            ticks.push_back(parse(line));  // Reuse the line parser
        } catch (const std::exception& e) {
            std::cerr << "Parse error: " << e.what() << " for line: " << line << std::endl;
        }
    }

    return ticks;
}
