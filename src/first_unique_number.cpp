#include <unordered_map>
#include <deque>
#include <vector>
#include "first_unique_number.hpp"


FirstUnique::FirstUnique(std::vector<int> &nums) : q(nums.begin(), nums.end()) {
    for (int x: nums) {
        um[x]++;
    }
}

int FirstUnique::showFirstUnique() {
    while (!q.empty() && um[q.front()] > 1) {
        q.pop_front();
    }
    return q.empty() ? -1 : q.front();
}

void FirstUnique::add(int value) {
    q.push_back(value);
    um[value]++;
}
