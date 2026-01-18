#pragma once
#include "std_aliases.hpp"

using namespace stl;

class PhoneDirectory {

public:
        PhoneDirectory(int maxNumbers);
        int get();
        bool check(int number);
        void release(int number);
private:
        deque<int> freeNumbers;
        vector<bool> used;
};