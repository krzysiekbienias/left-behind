#pragma once
#include <unordered_map>
#include <deque>

class FirstUnique {
public:
    std::unordered_map<int,int> um;
    std::deque<int> q;

    FirstUnique(std::vector<int>& nums);

    int showFirstUnique();
    void add(int value);

};