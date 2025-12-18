#pragma once

#include <string>
#include <iostream>
#include <deque>
#include <map>
#include <functional>   // std::greater
#include "order.hpp"

class OrderBook {
public:
    void addOrder(const Order& order);

    // dump całego booka dump dopowiadam za command query
    void dump(std::ostream& os) const;

    // dump z filtrami:
    // - symbolFilter: "" => wszystkie symbole
    // - tsFilter: nullopt => bez filtra czasu; w przeciwnym razie pokazuj tylko ordery o.timeStamp <= ts
    void dump(std::ostream& os,
              const std::string& symbolFilter,
              std::optional<int64_t> tsFilter) const;

private:
    using OrderQueue = std::deque<Order>;
    std::map<Price, OrderQueue, std::greater<Price>> buyBook;
    std::map<Price, OrderQueue> sellBook;
};