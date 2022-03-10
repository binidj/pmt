#include "KMP.h"

std::vector<int> KMP::Border = std::vector<int>();

void KMP::GetBorder(const Text& pattern)
{
	Border.assign(pattern.Length() + 1, 0);
	Border[0] = -1;
	int i = 1, j = 0;

	while (i + j < pattern.Length())
	{
		while (i + j < pattern.Length() && pattern[i + j] == pattern[j])
		{
			printf("%d %d", i, j);
			j++;
			Border[i + j] = j;
		}
		i += (j - Border[j]);
		j = std::max(0, Border[j]);
	}
}

const std::vector<size_t>& KMP::Search(const Text& text, const Text& pattern, bool BuildBorder)
{
	std::vector<size_t> Occurences;

	if (Border.size() == 0 || BuildBorder)
	{
		GetBorder(pattern);
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

		i = i + (j - Border[j]);
		j = std::max(0, Border[j]);
	}

	return Occurences;
}