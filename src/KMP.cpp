#include "KMP.h"

std::vector<int> KMP::GetBorder(const Text& pattern)
{
	std::vector<int> Border(pattern.Length() + 1);
	Border[0] = -1;
	int i = 1, j = 0;

	while (i + j < pattern.Length())
	{
		while (i + j < pattern.Length() && pattern[i + j] == pattern[j])
		{
			j++;
			Border[i + j] = j;
		}
		i += (j - Border[j]);
		j = std::max(0, Border[j]);
	}

	return Border;
}

void KMP::Init(const Text& pattern, const int EditDistance)
{
	Occurences.resize(1024);
	Border = GetBorder(pattern);
}

const int KMP::Search(const Text& text, const Text& pattern, const int EditDistance)
{
	CurrentOcc = 0;

	int i = 0, j = 0;
	int Limit = (int)text.Length() - (int)pattern.Length();
	
	while (i <= Limit)
	{
		while (j < pattern.Length() && text[i + j] == pattern[j])
		{
			j++;
		}
		
		if (j == pattern.Length())
		{
			if (CurrentOcc != Occurences.size())
				Occurences[CurrentOcc] = 1;
			else
				Occurences.emplace_back(i);
			CurrentOcc += 1;
		}

		i += j - Border[j];
		j = std::max(0, Border[j]);
	}

	return CurrentOcc;
}