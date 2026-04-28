#include <vector>
#include <unordered_map>
#include "randomized_set.hpp"

RandomizedSet::RandomizedSet() {}

bool RandomizedSet::insert(int val) {

    auto it=m_um.try_emplace(val);
    if (it.second) {
        m_v.push_back(val);
        m_um[val]=m_v.size()-1; //index is value
        return true;
    }
    return false;

}

bool RandomizedSet::remove(int val) {

}

int RandomizedSet::getRandom() {
    return -1;
}
