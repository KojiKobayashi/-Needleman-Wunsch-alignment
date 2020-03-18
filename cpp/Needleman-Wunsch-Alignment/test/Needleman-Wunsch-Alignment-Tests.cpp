#include "Needleman-Wunsch-Alignment-Tests.h"
#include "gtest/gtest.h"
#include "Needleman-Wunsch-Alignment.h"

TEST(FactorialTest, Pisitive) {
    EXPECT_EQ(2, nwa());
}

TEST(FactorialTest, Negative) {
    EXPECT_EQ(1, nwa());
}