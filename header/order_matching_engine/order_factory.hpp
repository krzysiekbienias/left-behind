#include "raw_order.hpp"
#include "order.hpp"


class OrderFactory {
public:
    Order createValidatedOrder(const RawOrder& raw) const;

    // helper: "104.53" -> 10453
    static Price parsePriceToCents(const std::string& s);

private:
    int validateOrderId(const std::string& orderIdToken) const;
    int64_t validateTimeStamp(const std::string& timeStampToken) const;
    OrderType validateOrderType(const std::string& orderTypeToken) const;
    Side validateSide(const std::string& sideToken) const;
    int validateQuantity(const std::string& quantityToken) const;

    Price validatePriceTicks(const std::string& priceToken, OrderType type) const;
};