#include "Needleman-Wunsch-Alignment-Tests.h"
#include "gtest/gtest.h"
#include "Needleman-Wunsch-Alignment.h"
using namespace Alignment;

namespace AlignmentTests
{
    TEST(AlignTest, Score)
    {
        auto ret = NeedlemanWunschAlignment::Align("GATTACA", "GCATGCU");
        ASSERT_EQ(0, ret.GetScore());

        ret = NeedlemanWunschAlignment::Align("abcde", "abcde");
        ASSERT_EQ(5, ret.GetScore());
    }

    TEST(AlignTest, ReturnString)
    {
        auto ret = NeedlemanWunschAlignment::Align("abcde", "abcde");
        ASSERT_EQ(1, ret.GetCandidateCount());
        auto retStrings = ret.GetStrings(0);
        ASSERT_EQ("abcde", retStrings.FirstString);
        ASSERT_EQ("abcde", retStrings.SecondString);

        ret = NeedlemanWunschAlignment::Align("GATTACA", "GCATGCU");
        ASSERT_EQ(3, ret.GetCandidateCount());

        retStrings = ret.GetStrings(0);
        ASSERT_EQ("G_ATTACA", retStrings.FirstString);
        ASSERT_EQ("GCA_TGCU", retStrings.FirstString);

        retStrings = ret.GetStrings(1);
        ASSERT_EQ("G_ATTACA", retStrings.FirstString);
        ASSERT_EQ("GCAT_GCU", retStrings.FirstString);

        retStrings = ret.GetStrings(2);
        ASSERT_EQ("G_ATTACA", retStrings.FirstString);
        ASSERT_EQ("GCATG_CU", retStrings.FirstString);
    }
}