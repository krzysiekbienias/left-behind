#pragma once
#include<vector>
#include "order.hpp"


class OrderParser{
public:
    RawOrder parserLine(const std::string& signal) const;
    std::vector<Order>parseOrdersStream(std::istream& input) const;
};

