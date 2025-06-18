#include "order_matching_engine/order_book.hpp"
#include "order_matching_engine/order.hpp"
#include "logger.hpp"


void OrderBook::addOrder(const Order& order) {
    if (order.side == 'B') {
        buyBook[order.price].push_back(order);
    } else if (order.side == 'S') {
        sellBook[order.price].push_back(order);
    } else {
        Logger::get()->error("{} - Reject - 303 - Unknown order side '{}'", order.orderId, order.side);
    }
}

void OrderBook::query() const {
    std::cout << "--- BUY BOOK ---\n";
    for (const auto& [price, orders] : buyBook) {
        std::cout << "Price: " << price << " => ";
        for (const auto& order : orders) {
            std::cout << "[ID=" << order.orderId << " Qty=" << order.quantity << "] ";
        }
        std::cout << "\n";
    }

    std::cout << "--- SELL BOOK ---\n";
    for (const auto& [price, orders] : sellBook) {
        std::cout << "Price: " << price << " => ";
        for (const auto& order : orders) {
            std::cout << "[ID=" << order.orderId << " Qty=" << order.quantity << "] ";
        }
        std::cout << "\n";
    }
}
