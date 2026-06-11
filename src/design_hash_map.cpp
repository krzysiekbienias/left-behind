#include <vector>
#include <list>
#include <design_hash_map.hpp>

MyHashMap::MyHashMap(): m_hm(m_n){}

void MyHashMap::put(int key, int value) {
    int index=key%m_n;
    std::list<std::pair<int,int>>& ll=m_hm[index];
    for (auto it=ll.begin();it!=ll.end();++it) {
        if (it->first==key) {
            it->second=value;
            return;
        }

    }

    ll.push_back({key,value});
}

int MyHashMap::get(int key) {
    int index=key%m_n;
    std::list<std::pair<int,int>>& ll=m_hm[index];
    for (auto it=ll.begin();it!=ll.end();++it) {
        if (it->first==key) {
            return it->second;
        }

    }
    return -1;
}

void MyHashMap::remove(int key) {
    int index=key%m_n;
    std::list<std::pair<int,int>>& ll=m_hm[index];
    for (auto it=ll.begin();it!=ll.end();++it) {
        if (it->first==key) {
            ll.erase(it);
            return;
        }

    }
    return;
}
