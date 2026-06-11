#include "randomized_set.hpp"

#include <cstdlib>
#include <unordered_map>
#include <vector>

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
    (void)val;
    return false;
}

int RandomizedSet::getRandom() {
    if (m_v.empty()) {
        return 0;
    }
    int randomIdx = std::rand() % m_v.size();
    return m_v[randomIdx];
}
