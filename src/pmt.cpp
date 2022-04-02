﻿// pmt.cpp : Defines the entry point for the application.
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
#include <unistd.h>
#include <map>
#include <memory>
#include <functional>

void PrintHelp()
{
	fprintf(stderr, "--------PMT--------\n");
	fprintf(stderr, "-------IF767-------\n\n");
	fprintf(stderr, "------FORMATO------\n");
	fprintf(stderr, "pmt [options] pattern textfile [textfile...]\n");
	fprintf(stderr, "options - CONFIRA SEÇÃO 'OPÇÕES ADICIONAIS'\n");
	fprintf(stderr, "patterns - Aho Corasick | BoyerMoore | Sellers | Sliding Window | Wu Manber \n");
	fprintf(stderr, "textfile - localização do arquivo de texto a ser utilizado.\n");
	fprintf(stderr, "	OBS: SE FOR UTILIZAR MAIS DE 1 ARQUIVO, É NECESSÁRIO COLOCAR COLCHETES\n");
	fprintf(stderr, "	EX: pmt 'Sellers' ['file1.txt', 'file2.txt']\n\n");
	fprintf(stderr, "--OPÇÕES ADICIONAIS--\n");
	fprintf(stderr, "-e | --edit emax - Localiza todas as ocorrencias aproximadas do padrao a uma distancia maxima emax\n");
	fprintf(stderr, "-p | --pattern patternfile - Realiza a busca de todos os padroes contidos no arquivo patternfile.\n");
	fprintf(stderr, "-a | --algorithm algorithm_name - Realiza a busca de padroes usando o algoritmo.\n");
	fprintf(stderr, "-c | --count - Imprime apenas a quantidade total de ocorrencias do(s) padrao(oes) contidas no(s) arquivo(s) de texto.\n");
	fprintf(stderr, "-h | --help - Imprime um manual básico de uso da aplicação\n");
}

void PrintUsage()
{

}

bool HasWildcards(const char* FileName)
{
	int len = strlen(FileName);
	for (int i = 0; i < len; i++)
	{
		if (FileName[i] == '*')
		{
			return true;
		}
	}
	return false;
}

int main(int argc, char** argv)
{
	int Option = -1;
	int EditDistance = -1;
	char PatternFile[128] = "";
	char AlgorithName[128] = "";
	char PatternArg[128] = "";
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

	bool HasPatternFile = false;
	int MinArgsRequired = 2;
	const int RemainingArgs = argc - optind;

	if (strcmp(PatternFile, "") != 0)
	{
		MinArgsRequired = 1;
		HasPatternFile = true;
	}
	else 
	{
		strcpy(PatternArg, argv[optind]);
		optind += 1;
	}

	if (RemainingArgs < MinArgsRequired)
	{
		fprintf(stderr,"Few arguments\n");
		PrintUsage();
		return 1;
	}

	char buffer[BufferSize];
	
	std::vector<Text> FileList;
	FileList.reserve(RemainingArgs);
	
	for (int FileIndex = optind; FileIndex < argc; FileIndex++)
	{
		if (HasWildcards(argv[FileIndex]))
		{
			// Regex check
			// emplace_back all files that match
		}
		else 
		{
			FileList.emplace_back(argv[FileIndex]);
		}
	}

	if (strcmp(AlgorithName, "") == 0)
		strcpy(AlgorithName, "boyer_moore");

	bool UsingKmp = strcmp(AlgorithName, "kmp") == 0;
	bool UsingBoyerMoore = strcmp(AlgorithName, "boyer_moore") == 0;
	bool UsingSellers = strcmp(AlgorithName, "sellers") == 0;
	bool UsingWuManber = strcmp(AlgorithName, "wu_manber") == 0;
	bool UsingAhoCorasick = strcmp(AlgorithName, "aho_corasick") == 0;

	const bool UsingSomeAlgorithm = UsingKmp + UsingBoyerMoore + UsingSellers + UsingWuManber + UsingAhoCorasick;
	if (!UsingSomeAlgorithm)
	{
		fprintf(stderr,"Error: Algorithm not supported/found\n");
		PrintUsage();
		return 1;
	}

	static const std::map<Text, std::function<std::unique_ptr<SinglePatternSearch>()>> StrategySelector = 
	{
		{"boyer_moore", []() -> std::unique_ptr<BoyerMoore> { return std::make_unique<BoyerMoore>(); }},
		{"kmp", []() -> std::unique_ptr<KMP> { return std::make_unique<KMP>(); }},
		{"sellers", []() -> std::unique_ptr<Sellers> { return std::make_unique<Sellers>(); }},
		{"wu_manber", []() -> std::unique_ptr<WuManber> { return std::make_unique<WuManber>(); }},
	};

	std::function<std::unique_ptr<SinglePatternSearch>()> StrategyInit = nullptr;
	if (!UsingAhoCorasick) StrategyInit = StrategySelector.at(Text(AlgorithName));

	std::vector<std::unique_ptr<SinglePatternSearch>> SearchStrategies;
	SearchStrategies.reserve(1024);
	std::vector<Text> PatternList;
	PatternList.reserve(1024);

	if (HasPatternFile)
	{
		FILE* fp = fopen(PatternFile, "r");
		if (fp == NULL)
		{
			fprintf(stderr,"Error: Pattern file \"%s\" does not exist\n", PatternFile);
			PrintUsage();
			return 1;
		}
		while (fgets(buffer, BufferSize, fp))
		{
			Text Pattern(buffer);
			if (UsingWuManber && Pattern.Length() > 64)
			{
				fprintf(stderr,"Warning: skiping search for \"%s\", wu_manber does not support large patterns.\n", PatternList.back().GetData());
			}
			else
			{
				PatternList.emplace_back(std::move(Pattern));
				if (!UsingAhoCorasick) SearchStrategies.emplace_back(StrategyInit());
			}
			if (!UsingAhoCorasick) SearchStrategies.back()->Init(PatternList.back(), EditDistance);
		}
		fclose(fp);
	}
	else 
	{
		PatternList.emplace_back(PatternArg);
		if (!UsingAhoCorasick) SearchStrategies.emplace_back(StrategyInit());
		if (UsingWuManber && PatternList.back().Length() > 64)
		{
			fprintf(stderr,"Warning: skiping pattern \"%s\", wu_manber does not support large patterns.\n", PatternList.back().GetData());
			return 0;
		}
		if (!UsingAhoCorasick) SearchStrategies.back()->Init(PatternList.back(), EditDistance);
	}
	
	long long TotalOccurrences = 0;
	long long LineOccurences = 0;

	// BenchmarkTimer benchmark;

	if (UsingAhoCorasick)
	{
		AhoCorasick::BuildFSM(PatternList);
	}

	{
		// BenchmarkTimer bench;
		for (const Text& File : FileList)
		{
			FILE *fp = fopen(File.GetData(), "r");
			
			if (fp == NULL)
			{
				fprintf(stderr,"Warning: skiping file \"%s\", text file does not exist\n", File.GetData());
				continue;
			}
			
			while (fgets(buffer, BufferSize, fp))
			{
				Text text(buffer, BufferSize); // Borrow pointer
				
				if (UsingAhoCorasick)
				{
					std::vector<std::pair<size_t, size_t>> Occurrences = AhoCorasick::Search(text, PatternList);
					LineOccurences = Occurrences.size();
					TotalOccurrences += LineOccurences;
				}
				else 
				{
					for (int i = 0; i < PatternList.size(); i++)
					{
						std::vector<size_t> Occurrences = SearchStrategies[i]->Search(text, PatternList[i], EditDistance);
						LineOccurences = Occurrences.size();
						TotalOccurrences += LineOccurences;	
					}
				}

				if (LineOccurences != 0 && !PrintCount)
				{
					printf("%s\n", buffer);
				}
			}
			
			fclose(fp);
		}
	}
	
	if (PrintCount)
		printf("%lld\n", TotalOccurrences);
	
	return 0;
}
