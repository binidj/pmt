#include "WuManber.h"

std::vector<std::bitset<MAX_BITS>> WuManber::CharMasks = std::vector<std::bitset<MAX_BITS>>();
std::vector<std::bitset<MAX_BITS>> WuManber::Errors = std::vector<std::bitset<MAX_BITS>>();
std::vector<std::bitset<MAX_BITS>> WuManber::NextErrors = std::vector<std::bitset<MAX_BITS>>();

void WuManber::GetCharMasks(const Text& pattern)
{
	CharMasks.assign(ALPHABET_SIZE, std::bitset<MAX_BITS>().set());
	for (int i = 0; i < pattern.Length(); i++)
	{
		CharMasks[pattern[i]].set(i, 0);
	}
}

const std::vector<size_t> WuManber::Search(const Text& text, const Text& pattern, const int EditDistance, const bool Rebuild)
{
	std::vector<size_t> Occurences;

	if (CharMasks.size() == 0)
	{
		GetCharMasks(pattern);
		Errors.reserve(EditDistance + 1);
		NextErrors.reserve(EditDistance + 1);
	}
	
	Errors[0] = std::bitset<MAX_BITS>().set();
	
	for (int i = 1; i <= EditDistance; i++)
	{
		Errors[i] = Errors[i-1] << 1;
	}

	for (int i = 0; i < text.Length(); i++)
	{
		NextErrors[0] = (Errors[0] << 1) | CharMasks[text[i]];
		for (int j = 1; j <= EditDistance; j++)
		{
			NextErrors[j] = ((Errors[j] << 1) | CharMasks[text[i]]) & (Errors[j-1] << 1) & (NextErrors[j-1] << 1) & (Errors[j - 1]);
		}
		
		Errors.swap(NextErrors);

		if (!Errors[EditDistance].test(pattern.Length() - 1))
		{
			Occurences.emplace_back(i);
		}
	}

	return Occurences;
}