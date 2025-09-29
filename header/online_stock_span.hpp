#pragma once
#include<vector>


class StockSpanner {
public:
    std:: vector<std::pair<int,int>> m_stack;
    int next(int price);
};