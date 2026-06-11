#include <vector>

#include <atm_machine.hpp>

ATM::ATM() {
    // TODO: initialize nbOfBanknots
}

void ATM::deposit(std::vector<int> banknotesCount) {
    (void)banknotesCount;
    // TODO: add banknotes to inventory
}

std::vector<int> ATM::withdraw(int amount) {
    (void)amount;
    // TODO: implement greedy withdraw
    return {-1};
}
