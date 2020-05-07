#pragma once

#include <string>
#include <vector>

namespace  Alignment
{
    struct AlignedStrings
    {
        std::string FirstString;
        std::string SecondString;
    };

    class AlignResults
    {
    private:
        int score = 0;
        std::vector<AlignedStrings> strings;
    public:
        AlignResults(int score);
        AlignResults(std::vector<AlignedStrings>& strings, int score);

        void AddStrings(AlignedStrings& strings);
        int GetScore() const;
        int GetCandidateCount() const;
        AlignedStrings GetStrings(int candidateIndex) const;
    };

    class NeedlemanWunschAlignment
    {
    public:
        static AlignResults Align(std::string first, std::string second, char separator = '_');

        // faster but only one string pair
        static AlignResults AlignOnePair(std::string first, std::string second, char separator = '_');
    };
}
