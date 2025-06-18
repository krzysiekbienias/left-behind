#pragma once
#include<string>
#include<iostream>
#include<deque>
#include"order.hpp"
#include <map>


class OrderBook {
private:
    using OrderQueue = std::deque<Order>;
    
    std::map<float, OrderQueue, std::greater<float>> buyBook;   // High to low
    std::map<float, OrderQueue> sellBook;
    
    
public:
    void query() const;
    void addOrder(const Order& order);
};
