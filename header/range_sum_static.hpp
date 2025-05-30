
#pragma once
#include<vector>

class RangeSum{
private:
    std::vector<int> m_prefixSum;
    
public:
    RangeSum(const std::vector<int>& nums);
   
    int sumRange(int left, int right);
    
};
