#include "order_matching_engine/order_book.hpp"
#include <iomanip>
#include <cstdlib> // std::llabs

static void printPrice(std::ostream &os, Price p) {
    auto whole = p / 100;
    auto frac = std::llabs(p % 100);
    os << whole << '.' << std::setw(2) << std::setfill('0') << frac;
    os << std::setfill(' ');
}

static bool passFilters(const Order &o,
                        const std::string &sym,
                        const std::optional<int64_t> &ts) {
    if (!sym.empty() && o.symbol != sym) return false;
    if (ts && o.timeStamp > *ts) return false; // "as-of": <= ts
    return true;
}

static int levelQty(const std::deque<Order> &q) {
    int sum = 0;
    for (const auto &o: q) sum += o.quantity;
    return sum;
}

void OrderBook::dump(std::ostream &os,
                     const std::string &symbolFilter,
                     std::optional<int64_t> tsFilter) const {
    os << "=========== ORDER BOOK ===========\n";

    os << "--- BUY (best -> worst) ---\n";
    bool anyBuy = false;
    for (const auto &[price, orders]: buyBook) {
        bool anyLevel = false;

        // najpierw sprawdź czy na tym poziomie jest coś po filtrach
        for (const auto &o: orders) {
            if (passFilters(o, symbolFilter, tsFilter)) {
                anyLevel = true;
                break;
            }
        }
        if (!anyLevel) continue;

        anyBuy = true;
        os << "PX=";
        printPrice(os, price);
        os << "  | ";

        for (const auto &o: orders) {
            if (!passFilters(o, symbolFilter, tsFilter)) continue;
            os << "[id=" << o.orderId << " symbol=" << o.symbol << " qty=" << o.quantity << " ts=" << o.timeStamp <<
                    "] ";
        }
        os << "\n";
    }
    if (!anyBuy) os << "(empty)\n";

    os << "--- SELL (best -> worst) ---\n";
    bool anySell = false;
    for (const auto &[price, orders]: sellBook) {
        bool anyLevel = false;
        for (const auto &o: orders) {
            if (passFilters(o, symbolFilter, tsFilter)) {
                anyLevel = true;
                break;
            }
        }
        if (!anyLevel) continue;

        anySell = true;
        os << "PX=";
        printPrice(os, price);
        os << "  | ";

        for (const auto &o: orders) {
            if (!passFilters(o, symbolFilter, tsFilter)) continue;
            os << "[id=" << o.orderId << " symbol=" << o.symbol << " qty=" << o.quantity << " ts=" << o.timeStamp <<
                    "] ";
        }
        os << "\n";
    }
    if (!anySell) os << "(empty)\n";

    os << "==================================\n";
}

void OrderBook::addOrder(const Order &order) {
    if (!liveIds.insert(order.orderId).second) {
        throw std::invalid_argument("duplicate orderIdL " + std::to_string(order.orderId));
    }
    if (order.side == Side::Buy) {
        buyBook[order.price].push_back(order);
        return;
    }
    if (order.side == Side::Sell) {
        sellBook[order.price].push_back(order);
    }
}
