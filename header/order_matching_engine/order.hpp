#pragma once
#include<string>
#include<iostream>
#include <std_aliases.hpp>

using namespace stl;


using Price=int64_t;

enum class Side {
    Buy,Sell
};

enum class OrderType {Market,Limit,IOC};


struct Order{

    int orderId{};
    int64_t timeStamp{};
    string symbol;
    OrderType orderType;
    Side side{};
    Price price{};
    int quantity{};

    friend std::ostream& operator<<(std::ostream& os, const Order& o) {
        auto sideStr = (o.side == Side::Buy) ? "B" : "S";

        const char* typeStr = "?";
        switch (o.orderType) {
            case OrderType::Market: typeStr = "M"; break;
            case OrderType::Limit:  typeStr = "L"; break;
            case OrderType::IOC:    typeStr = "I"; break;
        }

        auto printPrice = [&](Price p) {
            auto whole = p / 100;
            auto frac  = std::llabs(p % 100);
            os << whole << '.' << std::setw(2) << std::setfill('0') << frac;
            os << std::setfill(' ');
        };

        os << "Order{"
           << "id=" << o.orderId
           << ", ts=" << o.timeStamp
           << ", sym=" << o.symbol
           << ", type=" << typeStr
           << ", side=" << sideStr
           << ", price=";
        printPrice(o.price);
        os << ", qty=" << o.quantity
           << "}";

        return os;
    }
};
