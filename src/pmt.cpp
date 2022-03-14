// pmt.cpp : Defines the entry point for the application.
//

#include "pmt.h"
#include "Text.h"
#include "SlidingWindow.h"
#include "KMP.h"
#include "BoyerMoore.h"
#include "Sellers.h"
#include "WuManber.h"
#include "AhoCorasick.h"
#include <string.h>
#include <cstdio>
#include <stdio.h>

const int MAX_BUFFER_SIZE = 1024;

int main()
{
	char buffer[MAX_BUFFER_SIZE];
	
	FILE* fl;
	fopen_s(&fl, ".\\shakespeare_all_texts_lowercase.txt", "r");

	if (fl == NULL)
	{
		printf("File does not exist\n");
		return 0;
	}

	size_t OccAmount = 0, other = 0;

	while (fgets(buffer, MAX_BUFFER_SIZE, fl))
	{
		Text text(buffer);
		Text patt("love");
		std::vector<Text> PatternSet = { "love", "death", "conscience", "romeo", "juliet" };
		
		// std::vector<size_t>Occ = SlidingWindow::Search(text, patt);
		const std::vector<std::vector<size_t>> OccSet = AhoCorasick::Search(text, PatternSet);
		
		// printf("OccSet size %zu\n", OccSet.size());

		for (auto& vec : OccSet)
		{
			OccAmount += vec.size();
		}
	}

	printf("Found %zu occurences\n", OccAmount);

	fclose(fl);
	
	return 0;
}
