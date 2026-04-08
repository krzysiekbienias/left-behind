#pragma once
#include <vector>
#include <gtest/gtest.h>

class CustomStack {
public:
    CustomStack(int maxSize) ;

    void push(int x);

    int pop();

    void increment(int k, int val);

    friend class CustomStackTest; // Jeśli używasz klasowych testów w GTest
    FRIEND_TEST(CustomStack, TrivalCase);

private:
    int m_maxSize;
    std::vector<int> st;//vector disguised stack
    std::vector<int> lazy;
};

