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
		AlignResults(std::vector<Strings> strings, int score);
		void AddStrings(Strings strings);
		int GetScore();
		int GetCandidateCount();
		Strings GetStrings(int candidateIndex);
	};

	class NeedlemanWunschAlignment
	{
	public:
		static AlignResults NeedlemanWunschAlignment::Align(std::string first, std::string second);
	};
}
