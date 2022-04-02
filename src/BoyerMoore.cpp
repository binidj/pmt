#include "BoyerMoore.h"
#include "KMP.h"
#include <algorithm>

void BoyerMoore::GetBadChar(const Text& pattern)
{
	BadChar.assign(ALPHABET_SIZE, -1);
	for (int i = 0; i < pattern.Length(); i++)
	{
		BadChar[pattern[i]] = i;
	}
}

void BoyerMoore::GetGoodSuffix(const Text& pattern)
{
	int PatternSize = pattern.Length();
	
	Text rpattern(pattern);
	std::reverse(rpattern.begin(), rpattern.end());

	const std::vector<int> PatternBorder = KMP::GetBorder(pattern);
	const std::vector<int> ReverseBorder = KMP::GetBorder(rpattern);

	GoodSuffix.assign(PatternSize + 1, PatternSize - PatternBorder[PatternSize]);
	for (int i = 1; i < PatternSize; i++)
	{
		int j = (PatternSize - 1) - ReverseBorder[i];
		if (i - ReverseBorder[i] < GoodSuffix[j])
		{
			GoodSuffix[j] = i - ReverseBorder[i];
		}
	}
}

void BoyerMoore::Init(const Text& pattern, const int EditDistance)
{
	GetBadChar(pattern);
	GetGoodSuffix(pattern);
}

const std::vector<size_t> BoyerMoore::Search(const Text& text, const Text& pattern, const int EditDistance)
{
	std::vector<size_t> Occurences;

	int i = 0;
	int Limit = (int)text.Length() - (int)pattern.Length();

	while (i <= Limit)
	{
		int j = (int)pattern.Length() - 1;

		while (j >= 0 && text[i + j] == pattern[j])
		{
			j--;
		}

		if (j < 0)
		{
			Occurences.emplace_back(i);
			i += GoodSuffix.back();
		}
		else
		{
			i += std::max(GoodSuffix[j], j - BadChar[text[i + j]]);
		}
	}

	return Occurences;
}