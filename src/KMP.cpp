#include "KMP.h"

std::vector<int> KMP::Border = std::vector<int>();

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

const std::vector<size_t> KMP::Search(const Text& text, const Text& pattern, bool BuildBorder)
{
	std::vector<size_t> Occurences;

	if (Border.size() == 0 || BuildBorder)
	{
		Border = std::move(GetBorder(pattern));
	}

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
			Occurences.emplace_back(i);
		}

		i += j - Border[j];
		j = std::max(0, Border[j]);
	}

	return Occurences;
}