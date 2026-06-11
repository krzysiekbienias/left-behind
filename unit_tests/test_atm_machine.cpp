#include <gtest/gtest.h>

#include "atm_machine.hpp"

namespace {

std::vector<int> make_counts(int n20, int n50, int n100, int n200, int n500) {
    return {n20, n50, n100, n200, n500};
}

int total_value(const std::vector<int>& counts) {
    const int values[5] = {20, 50, 100, 200, 500};
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += counts[i] * values[i];
    }
    return sum;
}

}  // namespace

TEST(ATMTests, WithdrawFromEmptyReturnsMinusOne) {
    ATM atm;

    EXPECT_EQ(atm.withdraw(100), std::vector<int>({-1}));
}

TEST(ATMTests, WithdrawNonMultipleOfTenReturnsMinusOne) {
    ATM atm;
    atm.deposit(make_counts(1, 1, 1, 1, 1));

    EXPECT_EQ(atm.withdraw(15), std::vector<int>({-1}));
    EXPECT_EQ(atm.withdraw(123), std::vector<int>({-1}));
}

TEST(ATMTests, DepositThenWithdrawExactAmount) {
    ATM atm;
    atm.deposit(make_counts(0, 0, 1, 0, 1));  // 100 + 500 = 600

    const auto taken = atm.withdraw(600);
    ASSERT_EQ(taken.size(), 5);
    EXPECT_EQ(total_value(taken), 600);
    EXPECT_EQ(taken, make_counts(0, 0, 1, 0, 1));
}

TEST(ATMTests, WithdrawMoreThanAvailableReturnsMinusOne) {
    ATM atm;
    atm.deposit(make_counts(0, 0, 1, 0, 0));  // only 100

    EXPECT_EQ(atm.withdraw(200), std::vector<int>({-1}));
}

TEST(ATMTests, DepositAccumulatesAcrossCalls) {
    ATM atm;
    atm.deposit(make_counts(0, 0, 1, 0, 0));
    atm.deposit(make_counts(0, 0, 0, 1, 0));

    const auto taken = atm.withdraw(300);
    ASSERT_EQ(taken.size(), 5);
    EXPECT_EQ(total_value(taken), 300);
}

TEST(ATMTests, GreedyWithdrawUsesLargestNotesFirst) {
    ATM atm;
    atm.deposit(make_counts(0, 0, 1, 2, 1));

    const auto taken = atm.withdraw(600);
    EXPECT_EQ(taken, make_counts(0, 0, 1, 0, 1));
}

TEST(ATMTests, WithdrawFailsWhenExactChangeNotPossible) {
    ATM atm;
    atm.deposit(make_counts(0, 0, 1, 2, 1));

    atm.withdraw(600);
    EXPECT_EQ(atm.withdraw(250), std::vector<int>({-1}));
}

TEST(ATMTests, WithdrawZeroReturnsEmptyCounts) {
    ATM atm;
    atm.deposit(make_counts(1, 0, 0, 0, 0));

    const auto taken = atm.withdraw(0);
    ASSERT_EQ(taken.size(), 5);
    EXPECT_EQ(total_value(taken), 0);
    EXPECT_EQ(taken, make_counts(0, 0, 0, 0, 0));
}

TEST(ATMTests, RepeatedWithdrawUsesUpdatedInventory) {
    ATM atm;
    atm.deposit(make_counts(0, 2, 0, 0, 0));  // 2 x 50

    EXPECT_EQ(atm.withdraw(50), make_counts(0, 1, 0, 0, 0));
    EXPECT_EQ(atm.withdraw(50), make_counts(0, 1, 0, 0, 0));
    EXPECT_EQ(atm.withdraw(50), std::vector<int>({-1}));
}
