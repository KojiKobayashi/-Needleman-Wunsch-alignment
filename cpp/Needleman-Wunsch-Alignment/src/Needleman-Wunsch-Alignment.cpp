#include "Needleman-Wunsch-Alignment.h"


#include <algorithm>
#include <string>
#include <list>
//#include <minwindef.h>

namespace  Alignment
{
    AlignResults::AlignResults(int score)
    {
        this->score = score;
        this->strings = std::vector<Strings>();
    }

    AlignResults::AlignResults(std::vector<Strings> strings, int score)
    {
        this->score = score;
        this->strings = std::vector<Strings>{ strings };
    }

    void AlignResults::AddStrings(Strings strings)
    {
        this->strings.push_back(strings);
    }

    int AlignResults::GetScore()
    {
        return score;
    }

    int AlignResults::GetCandidateCount()
    {
        return strings.size();
    }

    Strings AlignResults::GetStrings(int candidateIndex)
    {
        auto tmp = strings.at(candidateIndex);
        return tmp;
    }

    AlignResults NeedlemanWunschAlignment::Align(std::string first, std::string second)
    {
        const auto separator = ' ';

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

        while (true)
        {
            if (r == 0 && c == 0)
            {
                std::reverse(alingA.begin(), alingA.end());
                std::reverse(alingB.begin(), alingB.end());
                Strings tmp = Strings{ alingA, alingB };
                results.AddStrings(tmp);
                // TODO:1個ならここでbreak
                break;
            }

            auto s = (r > 0 && c > 0 && first[r - 1] == second[c - 1]) ? 1 : -1;
            if (r > 0 && c > 0 && table[r][c] == table[r - 1][c - 1] + s)
            {
                alingA.push_back(first[r - 1]);
                alingB.push_back(second[c - 1]);
                r--;
                c--;
                continue;
            }

            if (r > 0 && table[r][c] == table[r - 1][c] - 1)
            {
                alingA.push_back(first[r - 1]);
                alingB.push_back(separator);
                r--;
                continue;
            }

            if (c > 0 && table[r][c] == table[r][c - 1] - 1)
            {
                alingA.push_back(separator);
                alingB.push_back(second[c - 1]);
                c--;
                continue;
            }

            // no search path
            break;
        }

        delete [] table;
        delete [] rawTable;

        return results;
    }


}
