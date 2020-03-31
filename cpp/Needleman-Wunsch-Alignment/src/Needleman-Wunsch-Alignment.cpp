#include "Needleman-Wunsch-Alignment.h"

#include <string>
#include <list>

namespace  Alignment
{
	int AlignResults::GetScore()
	{
		return 0;
	}

	int AlignResults::GetCandidateCount()
	{
		return 0;
	}
	
	Strings AlignResults::GetStrings(int candidateIndex)
	{
		return Strings();
	}

	AlignResults NeedlemanWunschAlignment::Align(std::string first, std::string second)
	{
		return AlignResults();
	}
}