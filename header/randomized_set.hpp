# pragma once
#include<unordered_map>
#include<vector>


class RandomizedSet {
public:
    RandomizedSet();

    bool insert(int val);

    bool remove(int val);

    int getRandom();

private:
    std::vector<int> m_v;
    std::unordered_map<int,int> m_um; //key is value we want to insert
};