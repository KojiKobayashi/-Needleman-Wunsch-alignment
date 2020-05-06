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

    class Aligner
    {
    private:
        std::string first;
        std::string second;
        char separator;
        int* rawTable = nullptr;
        int** table = nullptr;

    public:
        Aligner(std::string &first, std::string &second, const char separator)
        {
            this->first = first;
            this->second = second;
            this->separator = separator;
        }

        AlignResults Align()
        {
            std::list<Strings> stringsList;
            const auto r = first.length();
            const auto c = second.length();
            const std::string alignA, alignB;

            try
            {
                CreateTable();
                AlignResults results(table[r][c]);
                Iterate(r, c, alignA, alignB, results);

                delete[] table;
                delete[] rawTable;

                return results;
            }
            catch (...)
            {
                delete[] table;
                delete[] rawTable;
                throw;
            }
        }

    private:
        void CreateTable()
        {
            // create table
            const unsigned int rowSize = first.size() + 1U;
            const unsigned int colSize = second.size() + 1U;

            rawTable = new int[long long(colSize) * rowSize];
            table = new int* [rowSize];
            for (auto i = 0U; i < rowSize; i++)
                table[i] = rawTable + i * long long(colSize);

            for (auto i = 0U; i < colSize; i++)
                table[0][i] = -i;
            for (auto i = 0U; i < rowSize; i++)
                table[i][0] = -i;

            for (auto j = 0U; j < rowSize - 1U; j++)
            {
                for (auto i = 0U; i < colSize - 1U; i++)
                {
                    auto scoreBottom = table[j][i + 1] - 1;
                    auto scoreRight = table[j + 1][i] - 1;
                    auto scoreDiagonal = table[j][i] - 1;
                    if (first[j] == second[i])
                        scoreDiagonal += 2;
                    table[j + 1][i + 1] = std::max(scoreBottom, std::max(scoreRight, scoreDiagonal));
                }
            }
        }

        void Iterate(const size_t r, const size_t c, std::string alignA, std::string alignB, AlignResults& results)
        {
            if (r == 0 && c == 0)
            {
                std::reverse(alignA.begin(), alignA.end());
                std::reverse(alignB.begin(), alignB.end());
                auto tmp = Strings{ alignA, alignB };
                results.AddStrings(tmp);
                // TODO:1個ならここでbreak
                return;
            }

            if (r > 0 && c > 0)
            {
                const auto s = first[r - 1] == second[c - 1] ? 1 : -1;
                if (table[r][c] == table[r - 1][c - 1] + s)
                {
                    Iterate(r - 1, c - 1, alignA + first[r - 1], alignB + second[c - 1], results);
                }
            }

            if (r > 0 && table[r][c] == table[r - 1][c] - 1)
            {
                Iterate(r - 1, c, alignA + first[r - 1], alignB + separator, results);
            }

            if (c > 0 && table[r][c] == table[r][c - 1] - 1)
            {
                Iterate(r, c - 1, alignA + separator, alignB + second[c - 1], results);
            }
        }
    };

    AlignResults NeedlemanWunschAlignment::Align(std::string first, std::string second)
    {
        Aligner i(first, second, '_');
        return i.Align();
    }
}
