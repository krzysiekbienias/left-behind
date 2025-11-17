#pragma once

#include<std_aliases.hpp>

//LeetCode Shuffle an Array.

using namespace stl;

class ShuffleArray {
public:
    vector<int> mState;
    vector<int> mOrginal;



    ShuffleArray(vector<int>& nums);

    vector<int> reset();

    vector<int> shuffle();
};