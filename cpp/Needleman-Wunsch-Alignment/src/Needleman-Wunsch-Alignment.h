// Needleman-Wunsch-Alignment.h : 標準のシステム インクルード ファイル用のインクルード ファイル、
// または、プロジェクト専用のインクルード ファイル。

#pragma once

#include <string>
#include <list>

namespace  Alignment
{
	struct Strings
	{
		std::string FirstString;
		std::string SecondString;
	};
	
	class AlignResults
	{
		// int Score = 0;
	public:
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
