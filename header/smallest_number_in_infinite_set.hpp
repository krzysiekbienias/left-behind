# pragma once
# include <set>


class SmallestInfiniteSet {
public:
    SmallestInfiniteSet();

    int popSmallest();

    void addBack(int num);

private:
    std::set<int> addedBack;
    int nextFresh=1;
};