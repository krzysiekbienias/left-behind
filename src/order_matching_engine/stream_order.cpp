#include "order_matching_engine/raw_order.hpp"
#include "order_matching_engine/stream_order.hpp"
#include "order_matching_engine/order.hpp"
#include "order_matching_engine/order_factory.hpp"
#include "../utils/logger.hpp"
#include<vector>
#include<sstream>


RawOrder OrderParser::parserLine(const std::string& line) const{
    std::stringstream ss(line);
    std::string action;
    std::string orderId;
    std::string timeStamp;
    std::string symbol;
    std::string orderType;
    std::string side;
    std::string price;
    std::string quantity;
    
    
    std::getline(ss, action, ',');
    std::getline(ss, orderId, ',');
    std::getline(ss, timeStamp, ',');
    std::getline(ss, symbol, ',');
    std::getline(ss, orderType, ',');
    std::getline(ss, side, ',');
    std::getline(ss, price, ',');
    std::getline(ss, quantity, ',');
    
    
    
    
    return RawOrder{action,
        orderId,
        timeStamp,
        symbol,
        orderType,
        side,
        price,
        quantity,
    };
    
}

std::vector<Order> OrderParser::parseOrdersStream(std::istream &input) const{
    std::vector<Order> parsedOrders;
    std::string line;
    int lineNumber=0;
    OrderFactory orderFactory;
    
    while (std::getline(input, line)) {
        ++lineNumber;
        try {
            RawOrder rawOrder=parserLine(line);
            Order order =orderFactory.createValidatedOrder(rawOrder);
            parsedOrders.push_back(order);
        } catch (const std::exception& e) {
            Logger::get()->error("Line {}: Failed to process '{}'. Reason: {}", lineNumber, line, e.what());
        }
    }
    
    return parsedOrders;
}



