#include "market_data_normalization/json_parser.hpp"
#include "market_data_normalization/market_tick.hpp"
#include <nlohmann/json.hpp>
#include <vector>
#include <stdexcept>


std::vector<MarketTick> JSONParser::parseStream(std::istream& input) const{
    std::vector<MarketTick> ticks;
    nlohmann::json jsonData;
    input>>jsonData;
    if(!jsonData.is_array()){
        throw std::runtime_error("Expected a JSON array at the top level.");
    }
    
    for (const auto &obj :jsonData){
        ticks.push_back(MarketTick{
           obj.at("timestamp").get<std::string>(),
           obj.at("symbol").get<std::string>(),
           obj.at("bid").get<double>(),
           obj.at("ask").get<double>(),
        });
    }
    return ticks;
        
    
    
}

