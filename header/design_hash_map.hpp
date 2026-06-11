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
    int const m_n=10*10*10+9;
    std::vector<std::list<std::pair<int,int>>> m_hm;
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */