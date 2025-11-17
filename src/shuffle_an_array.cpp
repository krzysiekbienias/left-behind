

#include "shuffle_an_array.hpp"

#include<std_aliases.hpp>

using namespace stl;

ShuffleArray::ShuffleArray(vector<int>&nums):mState(nums),mOrginal(nums){}

vector<int>ShuffleArray::shuffle() {
    if (mState.empty()) return {};
    size_t n= mState.size()-1;
    static thread_local std::mt19937 rng(std::random_device{}()); //one generator, seed fixed once
    std::uniform_int_distribution<size_t> dist(0,n);
    size_t i=dist(rng);
    while (n>0) {
        std::swap(mState[n],mState[i]);
        n--;
    }
    return mState;
}

vector<int>ShuffleArray::reset() {
    return mOrginal;
}

