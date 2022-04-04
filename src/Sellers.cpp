#include "Sellers.h"
#include <numeric>
#include <cstdio>

void Sellers::GetNext(const Text& pattern, char Ch)
{
	NextColumn[0] = 0;
	for (int i = 1; i < NextColumn.size(); i++)
	{
		NextColumn[i] = std::min(Column[i] + 1, NextColumn[i - 1] + 1);
		const int Match = (Ch == pattern[i - 1]) ? 0 : 1;
		NextColumn[i] = std::min(NextColumn[i], Column[i - 1] + Match);
	}
}

void Sellers::Init(const Text& pattern, const int EditDistance)
{
	Occurences.resize(1024);
	Column.resize(pattern.Length() + 1);
	NextColumn.resize(pattern.Length() + 1);
}

const int Sellers::Search(const Text& text, const Text& pattern, const int EditDistance)
{
	CurrentOcc = 0;
	// std::vector<size_t> Occurences;
	// Occurences.reserve(text.Length());
	
	std::iota(Column.begin(), Column.end(), 0);

	for (size_t i = 0; i < text.Length(); i++)
	{
		GetNext(pattern, text[i]);
		Column.swap(NextColumn);
		if (Column.back() <= EditDistance)
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