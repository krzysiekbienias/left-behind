#include "order_matching_engine/order_factory.hpp"
#include "order_matching_engine/order.hpp"
#include "order_matching_engine/raw_order.hpp"

#include "order_matching_engine/parser_utils.hpp"
#include "../utils/logger.hpp"
#include "../utils/string_utils.hpp"

#include <stdexcept>

Order OrderFactory::createValidatedOrder(const RawOrder& raw) const {
    Order o;
    o.orderId   = validateOrderId(raw.orderId);
    o.timeStamp = validateTimeStamp(raw.timestamp);

    o.symbol = raw.symbol;
    if (o.symbol.empty()) throw std::invalid_argument("invalid symbol");

    o.orderType = validateOrderType(raw.orderType);
    o.side      = validateSide(raw.side);
    o.price     = validatePriceTicks(raw.price, o.orderType);
    o.quantity  = validateQuantity(raw.quantity);

    return o;
}

int OrderFactory::validateOrderId(const std::string& orderIdToken) const {
    int id = parse_utils::i32(orderIdToken, "orderId");
    if (id <= 0) throw std::invalid_argument("orderId must be positive");
    return id;
}

int64_t OrderFactory::validateTimeStamp(const std::string& timeStampToken) const {
    int64_t ts = parse_utils::i64(timeStampToken, "timestamp");
    if (ts < 0) throw std::invalid_argument("timestamp must be non-negative");
    return ts;
}

Side OrderFactory::validateSide(const std::string& sideToken) const {
    if (sideToken == "B") return Side::Buy;
    if (sideToken == "S") return Side::Sell;
    throw std::invalid_argument("unknown side");
}

OrderType OrderFactory::validateOrderType(const std::string& orderTypeToken) const {
    if (orderTypeToken == "M") return OrderType::Market;
    if (orderTypeToken == "L") return OrderType::Limit;
    if (orderTypeToken == "I") return OrderType::IOC;
    throw std::invalid_argument("unknown orderType");
}

int OrderFactory::validateQuantity(const std::string& qTok) const {
    int q = parse_utils::i32(qTok, "quantity");
    if (q <= 0) throw std::invalid_argument("quantity must be positive");
    return q;
}

Price OrderFactory::validatePriceTicks(const std::string& priceToken, OrderType type) const {
    if (type == OrderType::Market) return 0;

    Price p = parsePriceToCents(priceToken);
    if (p <= 0) throw std::invalid_argument("price must be > 0 for limit/IOC");
    return p;
}

Price OrderFactory::parsePriceToCents(const std::string& s) {
    if (s.empty()) throw std::invalid_argument("invalid price");

    int64_t whole = 0;
    int64_t frac = 0;
    bool seenDot = false;
    int fracDigits = 0;
    bool anyWholeDigit = false;

    for (char c : s) {
        if (c == '.') {
            if (seenDot) throw std::invalid_argument("invalid price");
            seenDot = true;
            continue;
        }
        if (c < '0' || c > '9') throw std::invalid_argument("invalid price");
        int d = c - '0';

        if (!seenDot) {
            anyWholeDigit = true;
            whole = whole * 10 + d;
        } else {
            if (fracDigits >= 2) throw std::invalid_argument("invalid price: too many decimals");
            frac = frac * 10 + d;
            ++fracDigits;
        }
    }

    // odrzuć ".50" i "10."
    if (!anyWholeDigit) throw std::invalid_argument("invalid price");
    if (seenDot && fracDigits == 0) throw std::invalid_argument("invalid price");

    if (fracDigits == 1) frac *= 10;
    if (fracDigits == 0) frac = 0;

    return whole * 100 + frac;
}