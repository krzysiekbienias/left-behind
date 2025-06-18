#pragma once

#include<string>
#include<vector>
#include "raw_order.hpp"

enum class CommandType{
    New,
    Amend,
    Cancel,
    Match,
    Query
}

struct Command{
    CommandType type;
    RawOrder rawOrder; //used for New, Amend
    std::string orderId; //used for Cancel, Query
    std::vector<std::string> tokens //full tokens
}

