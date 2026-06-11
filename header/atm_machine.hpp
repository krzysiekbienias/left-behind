#pragma once
#include <vector>

class ATM {
public:
    ATM();
    void deposit(std::vector<int> banknotesCount);
    std::vector<int> withdraw(int amount);
private:
    int values[5]={20,50,100,200,500}; //const table.
    long long nbOfBanknots[5];
};