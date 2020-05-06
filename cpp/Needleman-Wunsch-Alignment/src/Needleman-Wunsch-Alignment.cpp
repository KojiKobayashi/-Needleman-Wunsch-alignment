#include "Needleman-Wunsch-Alignment.h"


#include <algorithm>
#include <string>
#include <list>

namespace  Alignment
{
    AlignResults::AlignResults(const int score)
    {
        this->score = score;
        this->strings = std::vector<Strings>();
    }

    AlignResults::AlignResults(std::vector<Strings> &strings, const int score)
    {
        this->score = score;
        this->strings = std::vector<Strings>{ strings };
    }

    void AlignResults::AddStrings(Strings &strings)
    {
        this->strings.push_back(strings);
    }

    int AlignResults::GetScore() const
    {
        return score;
    }

    int AlignResults::GetCandidateCount() const
    {
        return strings.size();
    }

    Strings AlignResults::GetStrings(const int candidateIndex) const
    {
        auto tmp = strings.at(candidateIndex);
        return tmp;
    }

    void NeedlemanWunschAlignment::iterate(
        std::string first,
        std::string second,
        const char separator,
        int** table,
        AlignResults &results,
        std::string::size_type r,
        std::string::size_type c,
        std::string alingA,
        std::string alingB)
    {
        if (r == 0 && c == 0)
        {
            std::reverse(alingA.begin(), alingA.end());
            std::reverse(alingB.begin(), alingB.end());
            Strings tmp = Strings{ alingA, alingB };
            results.AddStrings(tmp);
            // TODO:1個ならここでbreak
            return;
        }

        auto s = (r > 0 && c > 0 && first[r - 1] == second[c - 1]) ? 1 : -1;
        if (r > 0 && c > 0 && table[r][c] == table[r - 1][c - 1] + s)
        {
            iterate(first, second, separator, table, results, r - 1, c - 1,
                alingA + first[r - 1], alingB + second[c - 1]);
        }

        if (r > 0 && table[r][c] == table[r - 1][c] - 1)
        {
            iterate(first, second, separator, table, results, r - 1, c,
                alingA + first[r - 1], alingB + separator);
        }

        if (c > 0 && table[r][c] == table[r][c - 1] - 1)
        {
            iterate(first, second, separator, table, results, r, c-1,
                alingA + separator, alingB + second[c - 1]);
        }

        return;
    }

    AlignResults NeedlemanWunschAlignment::Align(std::string first, std::string second)
    {
        const auto separator = '_';

        // create table
        const unsigned int rowSize = first.size() + 1U;
        const unsigned int colSize = second.size() + 1U;
        auto *rawTable = new int[long long(colSize) * rowSize];
        auto **table = new int* [rowSize];
        for (auto i = 0U; i < rowSize; i++)
            table[i] = rawTable + i * long long(colSize);

        for (auto i = 0U; i < colSize; i++)
            table[0][i] = -i;
        for (auto i = 0U; i < rowSize; i++)
            table[i][0] = -i;

        for (auto j = 0U; j < rowSize-1U; j++)
        {
            for (auto i = 0U; i < colSize-1U; i++)
            {
                auto scoreBottom = table[j][i + 1] - 1;
                auto scoreRight = table[j + 1][i] - 1;
                auto scoreDiagonal = table[j][i] - 1;
                if (first[j] == second[i])
                    scoreDiagonal += 2;
                table[j + 1][i + 1] = std::max(scoreBottom, std::max(scoreRight, scoreDiagonal));
            }
        }

        const auto score = table[rowSize - 1][colSize - 1];
        auto results = AlignResults(score);

        // run
        std::list<Strings> stringsList;
        auto r = first.length();
        auto c = second.length();
        std::string alingA, alingB;

        iterate(first, second, separator, table, results, r, c, alingA, alingB);

        delete [] table;
        delete [] rawTable;

        return results;
    }


}
