#pragma once
#include<string>
#include<iostream>

struct Order{
    char action;
    int orderId;
    int timeStamp;
    std::string symbol;
    char orderType;
    char side;
    float price;
    int quantity;
};


