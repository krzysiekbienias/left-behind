#include<vector>
#include "online_stock_span.hpp"

int StockSpanner::next(int price) {
    int span=1;
    while (!m_stack.empty() && m_stack.back().first<=price) {
        span+=m_stack.back().second;
        m_stack.pop_back();
    }
    m_stack.emplace_back(price,span);
    return span;
}
