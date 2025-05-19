#pragma once
#include<unordered_map>
#include<map>

class StockPrice{
private:
    int latestTimestamp=0; // to track the latest quatation of the stock, use for current
    std::unordered_map<int,int> timeStampToPrice; //update and overwrite at O(1)
    std::map<int,int> pricesToFrequences; // ordered by price, key is price
public:
    void update(int timeStamp, int price);
    int current();
    int maximum();
    int minimum();
};


