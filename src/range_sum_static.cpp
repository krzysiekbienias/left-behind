# include "range_sum_static.hpp"
# include <vector>

RangeSum::RangeSum(const std::vector<int>&nums){
    m_prefixSum.push_back(nums[0]);
    for (int i=1;i<nums.size();++i){
        m_prefixSum.push_back(m_prefixSum.back()+nums.at(i));
    }
    
}

int RangeSum::sumRange(int left, int right){
    if (left==0) {
        return m_prefixSum.at(right);
    }
    return m_prefixSum[right]-m_prefixSum[left-1];
}



