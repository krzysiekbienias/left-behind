#include<unordered_map>
#include<map>
#include <stock_price_combination.hpp>

void StockPrice::update(int timeStamp, int price){
    //Step 1: If timestamp already exists, we must correct its previous price
    if (timeStampToPrice.count(timeStamp)){
        int oldPrice=timeStampToPrice[timeStamp];
        pricesToFrequences[oldPrice]--;
        //Remove it from the map if the count becomes zero
        if(pricesToFrequences[oldPrice]==0){
            pricesToFrequences.erase(oldPrice);
        }
    }
    //Step 2: Update the timestamp-to-price map
    timeStampToPrice[timeStamp]=price;
    //Step 3: Increase frequency of the new price
    pricesToFrequences[price]++;
    
    //Step 4: Track the latest timestamp seen
    if (timeStamp>=latestTimestamp){
        latestTimestamp=timeStamp;
    }
}


int StockPrice::maximum(){
    return pricesToFrequences.rbegin()->first;
}

int StockPrice::minimum(){
    return pricesToFrequences.begin()->first;
    
}

int StockPrice::current(){
    return timeStampToPrice[latestTimestamp];
}
