#include "WuManber.h"

std::vector<unsigned long long> WuManber::CharMasks = std::vector<unsigned long long>();
std::vector<unsigned long long> WuManber::Errors = std::vector<unsigned long long>();
std::vector<unsigned long long> WuManber::NextErrors = std::vector<unsigned long long>();

void WuManber::GetCharMasks(const Text& pattern)
{
	CharMasks.resize(ALPHABET_SIZE, -1);
	for (int i = 0; i < pattern.Length(); i++)
	{
		CharMasks[pattern[i]] &= ~(1ULL << (unsigned long long)i);// .set(i, 0);
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

		if ((Errors[EditDistance] & (1ULL << (unsigned long long)(pattern.Length() - 1))) == 0) // !Errors[EditDistance].test(pattern.Length() - 1)
		{
			Occurences.emplace_back(i);
		}
	}

	return Occurences;
}