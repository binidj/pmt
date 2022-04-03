#include "WuManber.h"

void WuManber::GetCharMasks(const Text& pattern)
{
	CharMasks.resize(ALPHABET_SIZE, -1);
	for (int i = 0; i < pattern.Length(); i++)
	{
		CharMasks[pattern[i]] &= ~(1ULL << (unsigned long long)i);
	}
}

void WuManber::Init(const Text& pattern, const int EditDistance)
{
	GetCharMasks(pattern);
	Errors.reserve(EditDistance + 1);
	NextErrors.reserve(EditDistance + 1);
}

const std::vector<size_t> WuManber::Search(const Text& text, const Text& pattern, const int EditDistance)
{
	std::vector<size_t> Occurences;
	// Occurences.reserve(text.Length());
	
	Errors[0] = -1;
	
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

		if ((Errors[EditDistance] & (1ULL << (unsigned long long)(pattern.Length() - 1))) == 0)
		{
			Occurences.emplace_back(i);
		}
	}

	return Occurences;
}