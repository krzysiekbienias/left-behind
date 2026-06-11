#include "lru_cache_v2.hpp"


LRUCacheV2::LRUCacheV2(int capacity) : m_capacity(capacity) {
    // TODO: initialize cache internals if needed
}

int LRUCacheV2::get(int key) {
    auto it =m_index.find(key);
    if(it==m_index.end()){
        return -1;
    }
    m_lru.splice(m_lru.begin(),m_lru ,it->second);
    return it->second->second; //the same effect like m_lru.front().second;
    
}

void LRUCacheV2::put(int key, int value) {
    (void)key;
    (void)value;
    // TODO: implement O(1) insert/update + eviction
}
