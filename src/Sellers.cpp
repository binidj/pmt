#include "Sellers.h"
#include <numeric>

std::vector<int> Sellers::Column = std::vector<int>();
std::vector<int> Sellers::NextColumn = std::vector<int>();

void Sellers::GetNext(const Text& pattern, char Ch)
{
	std::fill(NextColumn.begin(), NextColumn.end(), 0);
	for (int i = 1; i < NextColumn.size(); i++)
	{
		NextColumn[i] = std::min(Column[i] + 1, NextColumn[i - 1] + 1);
		const int Match = (Ch == pattern[i - 1]) ? 0 : 1;
		NextColumn[i] = std::min(NextColumn[i], Column[i - 1] + Match);
	}
}

const std::vector<size_t>& Sellers::Search(const Text& text, const Text& pattern, const int Err)
{
	std::vector<size_t> Occurences;

	Column.assign(pattern.Length() + 1, 0);
	NextColumn.assign(pattern.Length() + 1, 0);

	std::iota(Column.begin(), Column.end(), 0);

	for (size_t i = 0; i < text.Length(); i++)
	{
		GetNext(pattern, text[i]);
		Column.swap(NextColumn);
		if (Column.back() <= Err)
		{
			Occurences.emplace_back(i);
		}
	}

	return Occurences;
}