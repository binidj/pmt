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
	char PatternArg[128];
	bool PrintCount = false;
	int BufferSize = 1024;
	bool Help = false;

	// incluir bool e opção indicando o uso de regex no textfile (pode ser letra w)

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

	int MinArgsRequired = 2;
	const int RemainingArgs = argc - optind;

	if (PatternFile != nullptr)
	{
		MinArgsRequired = 1;	
	}
	else 
	{
		strcpy(PatternArg, argv[optind]); // pattern passado no argumento 
		optind += 1;
	}

	if (RemainingArgs < MinArgsRequired)
	{
		fprintf(stderr,"Few arguments\n");
		PrintUsage();
		return 1;
	}

	char buffer[BufferSize];
	
	FILE* fl;
	fl = fopen(argv[optind], "r");
	// fl = fopen("./shakespeare_all_texts_lowercase.txt", "r");

	if (fl == NULL)
	{
		fprintf(stderr,"File %s does not exist\n", argv[optind]);
		// PrintUsage();
		// return 1;
	}

	bool IsSinglePattern = true;
	auto SinglePatternSearch = BoyerMoore::Search;
	auto MultiplePatternSearch = AhoCorasick::Search;

	// AlgorithName so pode conter single pattern, usar aho corasick somente via flag -p
	if (strcmp(AlgorithName, "boyer_moore") == 0) 
	{
		SinglePatternSearch = BoyerMoore::Search;
	}
	// else if ..
	// se algoritmo for Sellers/WuManber e EditDistance < 0 : printa erro de distancia invalida
	// se algoritmo for WuManber dar erro quando tamanho do padrão > 64

	if (PatternFile != nullptr)
	{
		IsSinglePattern = false;
	}
	
	// sem regex
	for (int FileIndex = optind; FileIndex < argc; FileIndex++)
	{
		// FILE* fl = fopen(argv[FileIndex], "r");
		// Rodar a busca pros arquivos nos argumentos
		// fclose(fl);
	}

	// com regex (so checa o padrao em optind)
	// checar todos os arquivos com match em argv[optind] (ver com paguso se diretorio corrente é suficiente)

	size_t OccAmount = 0, other = 0;

	{
		BenchmarkTimer benchmark;
		Text patt("coward");

		std::vector<Text> PatternSet = { "love", "death", "conscience", "romeo", "juliet" };
		while (fgets(buffer, BufferSize, fl))
		{
			printf("%s", buffer);
			Text text(buffer);
			
			std::vector<size_t>Occ = std::move(SinglePatternSearch(text, patt, EditDistance, false));
			// const std::vector<std::vector<size_t>> OccSet = AhoCorasick::Search(text, PatternSet);

			other += Occ.size();
			
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
