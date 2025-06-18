#include <gtest/gtest.h>
#include <sstream>
#include <iostream>
#include "print_utils.hpp" // adjust the path to match your project

using namespace print_utils;

class PrintUtilsTest : public ::testing::Test {
protected:
    std::stringstream buffer;
    std::streambuf* originalCout;

    void SetUp() override {
        originalCout = std::cout.rdbuf();
        std::cout.rdbuf(buffer.rdbuf());
    }

    void TearDown() override {
        std::cout.rdbuf(originalCout);
    }

    std::string getOutput() {
        return buffer.str();
    }
};

TEST_F(PrintUtilsTest, PrintVector) {
    printVector(std::vector<int>{1, 2, 3}, "vec");
    EXPECT_EQ(getOutput(), "vec: 1 2 3 \n");
}

TEST_F(PrintUtilsTest, PrintList) {
    printList(std::list<std::string>{"a", "b"}, "lst");
    EXPECT_EQ(getOutput(), "lst: a b \n");
}

TEST_F(PrintUtilsTest, PrintDeque) {
    printDeque(std::deque<char>{'x', 'y'}, "dq");
    EXPECT_EQ(getOutput(), "dq: x y \n");
}

TEST_F(PrintUtilsTest, PrintSet) {
    printSet(std::set<int>{3, 1, 2}, "set");
    EXPECT_EQ(getOutput(), "set: 1 2 3 \n");
}

TEST_F(PrintUtilsTest, PrintUnorderedSet) {
    std::unordered_set<std::string> us{"one", "two"};
    printUnorderedSet(us, "uset");
    std::string output = getOutput();
    EXPECT_TRUE(output.find("uset:") != std::string::npos);
    EXPECT_TRUE(output.find("one") != std::string::npos);
    EXPECT_TRUE(output.find("two") != std::string::npos);
}

TEST_F(PrintUtilsTest, PrintMap) {
    std::map<std::string, int> m{{"a", 1}, {"b", 2}};
    printMap(m, "mymap");
    EXPECT_EQ(getOutput(), "mymap:\n  a -> 1\n  b -> 2\n");
}

TEST_F(PrintUtilsTest, PrintUnorderedMap) {
    std::unordered_map<int, std::string> um{{1, "one"}, {2, "two"}};
    printUnorderedMap(um, "umap");
    std::string output = getOutput();
    EXPECT_TRUE(output.find("umap:") != std::string::npos);
    EXPECT_TRUE(output.find("1 -> one") != std::string::npos ||
                output.find("2 -> two") != std::string::npos);
}

TEST_F(PrintUtilsTest, PrintMapOfVectors) {
    std::map<std::string, std::vector<int>> m{
        {"first", {1, 2}},
        {"second", {3}}
    };
    printMapOfVectors(m, "mapVec");
    EXPECT_EQ(getOutput(), "mapVec:\n  first -> 1 2 \n  second -> 3 \n");
}

TEST_F(PrintUtilsTest, PrintVectorOfSets) {
    std::vector<std::set<int>> v{{1, 2}, {3}};
    printVectorOfSets(v, "vset");
    EXPECT_EQ(getOutput(), "vset:\n  [0]: 1 2 \n  [1]: 3 \n");
}

TEST_F(PrintUtilsTest, PrintMapOfDeque) {
    std::map<float, std::deque<std::string>> m{
        {1.5f, {"a", "b"}},
        {2.0f, {"c"}}
    };
    printMapOfDeque(m, "mapDq");
    EXPECT_EQ(getOutput(), "mapDq:\n  1.5: [a] [b] \n  2: [c] \n");
}
