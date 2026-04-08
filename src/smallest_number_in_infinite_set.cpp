#include "smallest_number_in_infinite_set.hpp"

SmallestInfiniteSet::SmallestInfiniteSet() {};

int SmallestInfiniteSet::popSmallest() {
    if (addedBack.empty()) return nextFresh++;//first return then increase
    auto it=addedBack.begin();
    int candidate=*it;
    addedBack.erase(it);
    return candidate;
}

void SmallestInfiniteSet::addBack(int num) {
    if (num>=nextFresh) return ;
    addedBack.insert(num);
}