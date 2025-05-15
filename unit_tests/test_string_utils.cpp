#include <gtest/gtest.h>
#include "string_utils.hpp"  // Adjust the path based on your project structure


using namespace StringUtils;

TEST(IsAllDigitsTest, ReturnsFalseOnEmptyString) {
    EXPECT_FALSE(isAllDigits(""));
}

TEST(IsAllDigitsTest, ReturnsTrueOnAllDigitString) {
    EXPECT_TRUE(isAllDigits("123456"));
    EXPECT_TRUE(isAllDigits("0"));
    EXPECT_TRUE(isAllDigits("000001"));
}

TEST(IsAllDigitsTest, ReturnsFalseOnStringWithLetters) {
    EXPECT_FALSE(isAllDigits("123a456"));
    EXPECT_FALSE(isAllDigits("abc"));
}

TEST(IsAllDigitsTest, ReturnsFalseOnStringWithSymbols) {
    EXPECT_FALSE(isAllDigits("123!"));
    EXPECT_FALSE(isAllDigits("12 34"));
    EXPECT_FALSE(isAllDigits("12.34"));
    EXPECT_FALSE(isAllDigits("12-34"));
}

TEST(IsAllDigitsTest, HandlesLargeNumericString) {
    std::string largeNumeric(1000, '9');
    EXPECT_TRUE(isAllDigits(largeNumeric));
}
