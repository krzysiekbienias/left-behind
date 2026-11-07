#include <vector>
#include <list>
#include <design_hash_map.hpp>

MyHashMap::MyHashMap(): table_(BUCKETS){}

void MyHashMap::put(int key, int value) {
    auto &bucket=table_[hash(key)];
    for (auto& [k, v] : bucket) {
        if(k==key){
            v=value;
            return;
        }
        bucket.emplace_back(key,value);
    }

    }

    


int MyHashMap::get(int key) {
    const auto & bucket=table_[hash(key)];
    for (const auto & [k,v]:bucket){
        if(k==key){
            return v;
        }
    }
    return -1;
    }


void MyHashMap::remove(int key) {
    auto &bucket =table_[hash(key)];
    //linear traverse through ll
    for (auto it=bucket.begin();it!=bucket.end();++it){
        if(it->first==key){
            bucket.erase(it);
            return;
        }
    }
}
