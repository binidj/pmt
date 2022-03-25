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
#include <cstddef>
#include <cstdint>
#include <unistd.h>

void PrintHelp()
{

}

void PrintUsage()
{

}

int main(int argc, char** argv)
{
	int Option = -1;
	int EditDistance = -1;
	char PatternFile[128];
	char AlgorithName[128];
	bool PrintCount = false;
	int BufferSize = 1024;
	bool Help = false;

	while ((Option = getopt(argc, argv, "a:b:ce:hp:")) != -1)
	{
		switch (Option)
		{
			case 'e':
				EditDistance = atoi(optarg);
				break;
			
			case 'p':
				strcpy(PatternFile, optarg);
				break;

			case 'a':
				strcpy(AlgorithName, optarg);
				break;
			
			case 'c':
				PrintCount = true;
				break;

			case 'b':
				BufferSize = atoi(optarg);
				break;

			case '?':
				if (optopt == 'e' || optopt == 'p' || optopt == 'a' || optopt == 'b')
					fprintf(stderr, "Option -%c requires an argument.\n", optopt);
				else if (isprint(optopt))
					fprintf(stderr, "Unknown option '-%c'.\n", optopt);
				else
					fprintf(stderr, "Unknown option character '\\x%x'.\n", optopt);
				PrintUsage();
				return 1;
				break;

			default:
				abort();
				break;
		}	
	}
	
	if (Help)
	{
		PrintHelp();
		return 0;
	}

	char buffer[BufferSize];
	
	FILE* fl;
	fl = fopen(argv[optind], "r"); // descobrir como ler multiplos arquivos com regex (ex: file*.txt)
	// fl = fopen("./shakespeare_all_texts_lowercase.txt", "r");

	if (fl == NULL)
	{
		printf("File %s does not exist\n", argv[optind]);
		return 0;
	}

	size_t OccAmount = 0, other = 0;

	{
		BenchmarkTimer benchmark;
		Text patt("coward");

		std::vector<Text> PatternSet = { "love", "death", "conscience", "romeo", "juliet" };
		while (fgets(buffer, BufferSize, fl))
		{
			printf("%s", buffer);
			Text text(buffer);
			
			// std::vector<size_t>Occ = Sellers::Search(text, patt, 2);
			const std::vector<std::vector<size_t>> OccSet = AhoCorasick::Search(text, PatternSet);

			// other += Occ.size();
			
			// for (auto& vec : OccSet)
			// {
			// 	OccAmount += vec.size();
			// }
		}
	}

	printf("Found %zu occurences\n", OccAmount);
	printf("%zu\n", other);

	fclose(fl);
	
	return 0;
}
