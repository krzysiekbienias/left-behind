#include "gtest/gtest.h"
#include "design_stack_with_increment_operation.hpp"




TEST(CustomStack,TrivalCase) {
    CustomStack cs(3);
    cs.push(1);
    cs.push(2);
    cs.pop();
    cs.push(2);
    cs.push(3);
    cs.push(4);
    cs.increment(5,100);
    EXPECT_EQ(cs.st.back(),103);

}

