#include "order_matching_engine/raw_order.hpp"
#include "order_matching_engine/order.hpp"
#include "order_matching_engine/order_factory.hpp"

Order OrderFactory::createValidatedOrder(const RawOrder& raw)const {
    char action =validateAction(raw.action);
    int orderId= validateOrderId(raw.orderId);
    int timeStamp= validateTimeStamp(raw.timestamp);
    std::string symbol=raw.symbol; //missing validation
    char orderType=validateOrderType(raw.orderType);
    char side=validateSide(raw.side);
    float price=validatePrice(raw.price);
    int quantity=validateQuantity(raw.quantity);
    return Order{action,orderId,timeStamp,symbol,orderType,side,price,quantity};
    
}


char OrderFactory::validateAction(const std::string& actionToken) const{
    if (actionToken.size() != 1 || std::string("NAXMQ").find(actionToken[0]) == std::string::npos) {
            throw std::invalid_argument("Invalid action code: " + actionToken);
        }
        return actionToken[0];
    
}

int OrderFactory::validateOrderId(const std::string& orderIdToken) const{
    try{
        int orderId=std::stoi(orderIdToken);
        if (orderId<=0){
            throw std::invalid_argument("Order Id must be positive number "+orderIdToken);
            
        }
        return orderId;
    }
    catch(const std::exception& e){
        throw std::invalid_argument("invalid order ID "+orderIdToken);
    }
}

int OrderFactory::validateTimeStamp(const std::string& timeStampToken) const{
    try {
        int timeStamp=std::stoi(timeStampToken);
        if (timeStamp<0) {
            throw std::invalid_argument("Time stamp must be positive "+ timeStampToken);
            
        }
        return timeStamp;
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid time stamp.");
    }
    
}


char OrderFactory::validateSide(const std::string & sideToken) const{
    if (sideToken.size()!=1 || std::string("BS").find(sideToken[0])==std::string::npos) {
        throw std::invalid_argument("Side side might be only B or S");
    }
    return sideToken[0];
    
}

char OrderFactory::validateOrderType(const std::string &orderTypeToken)const{
    if (orderTypeToken.size()!=1 || std::string("MLI").find(orderTypeToken[0])==std::string::npos) {
        throw std::invalid_argument("Order type might be only M(market), L(Limit) or I(IOC).");
    }
    return orderTypeToken[0];
    
}

float OrderFactory::validatePrice(const std::string &priceToken) const{
    try {
        float price=std::stof(priceToken);
        if (price<0) {
            throw std::invalid_argument("Time stamp must be positive "+ priceToken);
            
        }
        return price;
    } catch (const std::exception& e) {
        throw std::invalid_argument("Invalid time stamp.");
    }
    
}

int OrderFactory::validateQuantity(const std::string &quantityToken) const{
    try{
        int quantity=std::stoi(quantityToken);
        if (quantity<=0){
            throw std::invalid_argument("Order Id must be positive number "+quantityToken);
            
        }
        return quantity;
    }
    catch(const std::exception& e){
        throw std::invalid_argument("invalid order ID "+quantityToken);
    }
}


