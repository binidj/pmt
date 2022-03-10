// pmt.cpp : Defines the entry point for the application.
//

#include "pmt.h"
#include "Text.h"
#include "SlidingWindow.h"
#include "KMP.h"
#include "BoyerMoore.h"
#include <string.h>
#include <cstdio>
#include <stdio.h>

const int MAX_BUFFER_SIZE = 1024;

int main()
{
	char buffer[MAX_BUFFER_SIZE];
	
	FILE* fl;
	fopen_s(&fl, ".\\meme.txt", "r");

	if (fl == NULL)
	{
		printf("File does not exist");
		return 0;
	}

	while (fgets(buffer, MAX_BUFFER_SIZE, fl))
	{
		Text text(buffer);
		Text patt("love");
		std::vector<size_t>Occ = BoyerMoore::Search(text, patt);
		printf("LINE: %s", text.GetData());
		printf("Found %zu occurences\n", Occ.size());
		// Do algorithm
	}

	fclose(fl);
	// int kk = __std_get_string_size_without_trailing_whitespace();
	
	// std::string kk = "fsafasfsa\n";
	// std::cout << kk;
	// printf("%s %zu", meme.GetData(), meme.Length());
	
	return 0;
}
