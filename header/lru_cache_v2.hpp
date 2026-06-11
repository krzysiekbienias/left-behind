#pragma once

#include <list>
#include <unordered_map>

class LRUCacheV2 {
public:
    explicit LRUCacheV2(int capacity);
    int get(int key);
    void put(int key, int value);

private:
    using Entry = std::pair<int, int>; // key, value
    using List = std::list<Entry>;
    using ListIt = List::iterator;

    int m_capacity;
    List m_lru; // front = most recently used, back = least recently used
    std::unordered_map<int, ListIt> m_index;
};
