#include "Needleman-Wunsch-Alignment-Tests.h"
#include "gtest/gtest.h"
#include "Needleman-Wunsch-Alignment.h"

TEST(AlignTest, Score)
{
    auto ret = NeedlemanWunschAlign.Aling("GATTACA", "GCATGCU");
    ASSERT_EQ(0, ret.Score);

    ret = NeedlemanWunschAlign.Aling("abcde", "abcde");
    ASSERT_EQ(5, ret.Score);
}

TEST(AlignTest, ReturnString)
{
    auto ret = NeedlemanWunschAlign.Aling("abcde", "abcde");
    ASSERT_EQ(1, ret.Candidates.size);
    ASSERT_EQ(2, ret.Candidates[0].Str.size);
    ASSERT_EQ("abcde", ret.Candidates[0].Str[0]);
    ASSERT_EQ("abcde", ret.Candidates[0].Str[1]);

    auto ret = NeedlemanWunschAlign.Aling("GATTACA", "GCATGCU");
    ASSERT_EQ(3, ret.Candidates.size);
    ASSERT_EQ("G_ATTACA", ret.Candidates[0].Str[0]);
    ASSERT_EQ("GCA_TGCU", ret.Candidates[0].Str[1]);
    ASSERT_EQ("G_ATTACA", ret.Candidates[1].Str[0]);
    ASSERT_EQ("GCAT_GCU", ret.Candidates[1].Str[1]);
    ASSERT_EQ("G_ATTACA", ret.Candidates[2].Str[0]);
    ASSERT_EQ("GCATG_CU", ret.Candidates[2].Str[1]);
}