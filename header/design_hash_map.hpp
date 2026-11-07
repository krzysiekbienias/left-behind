#pragma once
#include<vector>
#include <list>

class MyHashMap {
public:

    MyHashMap();

    void put(int key, int value);

    int get(int key);

    void remove(int key);
private:
    static const int BUCKETS=10007;
    std::vector<std::list<std::pair<int,int>>> table_;
    //helper function
    int hash (int key){
        return key%BUCKETS;
    };
};
