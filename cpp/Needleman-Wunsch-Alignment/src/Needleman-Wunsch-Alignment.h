// Needleman-Wunsch-Alignment.h : 標準のシステム インクルード ファイル用のインクルード ファイル、
// または、プロジェクト専用のインクルード ファイル。

#pragma once

#include <string>
#include <vector>

namespace  Alignment
{
	struct Strings
	{
		std::string FirstString;
		std::string SecondString;
	};
	
	class AlignResults
	{
	private:
		int score = 0;
		std::vector<Strings> strings;
	public:
		AlignResults(int score);
		AlignResults(std::vector<Strings> &strings, int score);
		void AddStrings(Strings &strings);
		int GetScore() const;
		int GetCandidateCount() const;
		Strings GetStrings(int candidateIndex) const;
	};

	class NeedlemanWunschAlignment
	{
	private:
        static void iterate(std::string first, std::string second, char separator, int** table, AlignResults &results,
                            std::string::size_type r, std::string::size_type c, std::string alingA, std::string alingB
                            );
	public:
		static AlignResults NeedlemanWunschAlignment::Align(std::string first, std::string second);
	};
}
