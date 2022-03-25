#include "SlidingWindow.h"

const std::vector<size_t> SlidingWindow::Search(const Text& text, const Text& pattern)
{
	std::vector<size_t> Occurences;
	int Limit = (int)text.Length() - (int)pattern.Length();
	for (int i = 0; i <= Limit; i++)
	{
		int j = 0;
		for (; i + j < text.Length() && j < pattern.Length(); j++)
		{
			if (text[i + j] != pattern[j])
			{
				break;
			}
		}
		if (j == pattern.Length())
		{
			Occurences.emplace_back(i);
		}
	}
	return Occurences;
}