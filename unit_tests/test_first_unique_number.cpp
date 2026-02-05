// test_first_unique.cpp
#include <gtest/gtest.h>
#include <vector>



#include "first_unique_number.hpp"  // <-- adjust filename if yours differs

TEST(FirstUniqueTests, ConstructorKeepsOrderAndReturnsFirstUnique) {
    std::vector<int> nums{2, 3, 5};
    FirstUnique fu(nums);

    EXPECT_EQ(fu.showFirstUnique(), 2);
}

TEST(FirstUniqueTests, ReturnsMinusOneWhenAllAreDuplicates) {
    std::vector<int> nums{1, 1, 1, 1};
    FirstUnique fu(nums);

    EXPECT_EQ(fu.showFirstUnique(), -1);
}

TEST(FirstUniqueTests, SkipsDuplicatesAndFindsNextUniqueAfterAdds) {
    std::vector<int> nums{2, 3, 5};
    FirstUnique fu(nums);

    EXPECT_EQ(fu.showFirstUnique(), 2);

    fu.add(5); // 5 becomes duplicate
    EXPECT_EQ(fu.showFirstUnique(), 2);

    fu.add(2); // 2 becomes duplicate
    EXPECT_EQ(fu.showFirstUnique(), 3);

    fu.add(3); // 3 becomes duplicate
    EXPECT_EQ(fu.showFirstUnique(), -1);
}

TEST(FirstUniqueTests, ConstructorWithLeadingDuplicatesFindsUniqueLater) {
    std::vector<int> nums{7, 7, 8, 8, 9};
    FirstUnique fu(nums);

    EXPECT_EQ(fu.showFirstUnique(), 9);
}

TEST(FirstUniqueTests, AddNewUniqueDoesNotOverrideEarlierUniqueUntilItBecomesDuplicate) {
    std::vector<int> nums{4, 4, 6};
    FirstUnique fu(nums);

    EXPECT_EQ(fu.showFirstUnique(), 6);

    fu.add(7); // 7 is unique but appears after 6
    EXPECT_EQ(fu.showFirstUnique(), 6);

    fu.add(6); // 6 becomes duplicate now
    EXPECT_EQ(fu.showFirstUnique(), 7);
}

TEST(FirstUniqueTests, EmptyInitializationThenAddWorks) {
    std::vector<int> nums{};
    FirstUnique fu(nums);

    EXPECT_EQ(fu.showFirstUnique(), -1);

    fu.add(10);
    EXPECT_EQ(fu.showFirstUnique(), 10);

    fu.add(10);
    EXPECT_EQ(fu.showFirstUnique(), -1);
}

TEST(FirstUniqueTests, RepeatedShowFirstUniqueIsStable) {
    std::vector<int> nums{1, 1, 2, 3, 3};
    FirstUnique fu(nums);

    EXPECT_EQ(fu.showFirstUnique(), 2);
    EXPECT_EQ(fu.showFirstUnique(), 2);
    EXPECT_EQ(fu.showFirstUnique(), 2);
}

TEST(FirstUniqueTests, AddDuplicateDoesNotChangeIfFrontStillUnique) {
    std::vector<int> nums{1, 2, 3};
    FirstUnique fu(nums);

    EXPECT_EQ(fu.showFirstUnique(), 1);

    fu.add(2); // 2 becomes duplicate, but 1 still unique
    EXPECT_EQ(fu.showFirstUnique(), 1);
}
