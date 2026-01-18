#include "phone_directory.hpp"

#include <std_aliases.hpp>
using namespace stl;
using namespace io;


PhoneDirectory::PhoneDirectory(int maxNumbers) : used(maxNumbers, true), freeNumbers() {
    for (int i = 0; i < maxNumbers; ++i) {
        freeNumbers.push_back(i);
    }
    auto temp = freeNumbers;
    //DEBUG
    cout << "Free numbers: ";
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop_front();
    }
    cout << endl;
}

int PhoneDirectory::get() {
    if (!freeNumbers.empty()) {
        int firstFreeSlot = freeNumbers.front();
        freeNumbers.pop_front();
        used[firstFreeSlot] = false;
        return firstFreeSlot;
    }
    return -1;
}

bool PhoneDirectory::check(int number) {
    return used[number];
}

void PhoneDirectory::release(int number) {
    if (used[number] == true) return;
    else {
        used[number] = true;
        freeNumbers.push_back(number);
    }
}
