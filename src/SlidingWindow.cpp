#include "SlidingWindow.h"

void SlidingWindow::Init(const Text& pattern, const int EditDistance)
{
	Occurences.resize(1024);
}

const int SlidingWindow::Search(const Text& text, const Text& pattern, const int EditDistance)
{
	CurrentOcc = 0;
	// std::vector<size_t> Occurences;
	// Occurences.reserve(text.Length());

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
			if (CurrentOcc != Occurences.size())
				Occurences[CurrentOcc] = i;
			else
				Occurences.emplace_back(i);
			CurrentOcc += 1;
		}
	}
	return CurrentOcc;
}