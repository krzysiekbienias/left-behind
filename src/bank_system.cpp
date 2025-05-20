#include<vector>
#include "bank_system.hpp"


Bank::Bank(const std::vector<long long>& balance):m_balance(balance){};


const std::vector<long long> Bank::getBalances() const{
    return m_balance;
}

bool Bank::isAccountValid(int account){
    if (account>=1 && account<=m_balance.size()){
        return true;
        
    }
    else return false;
}

bool Bank::deposit(int account, long long money){
    if (Bank::isAccountValid(account)){
        m_balance[account-1]+=money;
        return true;
    }
    return false;
}

bool Bank::withdraw(int account, long long money){
    if (Bank::isAccountValid(account) && money<=m_balance.at(account-1)) {
        m_balance[account-1]-=money;
        return true;
    }
    else return false;
}



bool Bank::transfer(int account1, int account2, long long money){
    if (Bank::isAccountValid(account1) && Bank::isAccountValid(account2) && money<=m_balance.at(account1-1)) {
        m_balance[account1-1]-=money;
        m_balance[account2-1]+=money;
        return true;
    }
    return false;
}
