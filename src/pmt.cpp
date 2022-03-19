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
#include "BenchmarkTimer.h"
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

	{
		BenchmarkTimer benchmark;
		Text patt("coward");
		while (fgets(buffer, MAX_BUFFER_SIZE, fl))
		{
			Text text(buffer);
			
			std::vector<size_t>Occ = WuManber::Search(text, patt, 2);
			
			other += Occ.size();
		}
	}

	printf("Found %zu occurences\n", OccAmount);
	printf("%zu\n", other);

	fclose(fl);
	
	return 0;
}
