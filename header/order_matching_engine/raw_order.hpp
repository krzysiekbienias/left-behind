#pragma once
#include<string>

//only caries data for futher validation
struct RawOrder {
    std::string action;
    std::string orderId;
    std::string timestamp;
    std::string symbol;
    std::string orderType;
    std::string side;
    std::string price;
    std::string quantity;
};
