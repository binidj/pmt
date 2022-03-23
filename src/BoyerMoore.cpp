#include "BoyerMoore.h";
#include "KMP.h";
#include <algorithm>

std::vector<int> BoyerMoore::BadChar = std::vector<int>(ALPHABET_SIZE, -1);

std::vector<int> BoyerMoore::GoodSuffix = std::vector<int>();

void BoyerMoore::GetBadChar(const Text& pattern)
{
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

	const std::vector<int> PatternBorder = std::move(KMP::GetBorder(pattern));
	const std::vector<int> ReverseBorder = std::move(KMP::GetBorder(rpattern));

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

const std::vector<size_t>& BoyerMoore::Search(const Text& text, const Text& pattern, bool BuildHeuriscts)
{
	std::vector<size_t> Occurences;

	if (BadChar.size() == 0 || GoodSuffix.size() == 0 || BuildHeuriscts)
	{
		GetBadChar(pattern);
		GetGoodSuffix(pattern);
	}

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