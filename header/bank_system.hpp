#pragma once
#include<vector>



class Bank{
private:
    std::vector<long long> m_balance;
    bool isAccountValid(int account);
    
    
public:
    
    Bank(const std::vector<long long>& balance);
    
    const std::vector<long long> getBalances() const;
    bool transfer(int account1, int account2, long long money);
    bool deposit(int account, long long money);
    bool withdraw(int account, long long money);
};
