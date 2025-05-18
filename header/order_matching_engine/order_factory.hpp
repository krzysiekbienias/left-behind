#include "raw_order.hpp"


class OrderFactory{
public:
    Order createValidatedOrder(const RawOrder& raw) const;
    
private:
    char validateAction(const std::string& actionToken)const;
    int validateOrderId(const std::string& orderIdToken)const;
    int validateTimeStamp(const std::string& timeStampToken)const;
    char validateOrderType(const std::string& orderTypeToken)const;
    char validateSide(const std::string& sideToken)const;
    float validatePrice(const std::string& priceToken)const;
    int validateQuantity(const std::string& quantityToken,const std::string& orderIdToken)const;
};
