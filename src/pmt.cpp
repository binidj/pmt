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
#include <getopt.h>
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

int main(int argc, char** argv)
{
	static int Option = -1;
	static int EditDistance = 0;
	static char PatternFile[128] = "";
	static char AlgorithName[128] = "";
	static char PatternArg[128] = "";
	static bool PrintCount = false;
	static bool Help = false;
	static bool OptAhoCorasick = true;

	static int OptionIndex = 0;

	static struct option LongOptions[] =
	{
		{"count", no_argument, 0, 'c'},
		{"help", no_argument, 0, 'h'},
		{"no_ac_opt", no_argument, 0, 'n'},
		{"algorithm", required_argument, 0, 'a'},
		{"pattern", required_argument, 0, 'p'},
		{"edit", required_argument, 0, 'e'},
	};
	
	while ((Option = getopt_long(argc, argv, "a:ce:hnp:", LongOptions, &OptionIndex)) != -1)
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
			
			case 'h':
				Help = true;
				break;

			case 'n':
				OptAhoCorasick = false;
				break;

			case '?':
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
	else if (RemainingArgs != 0) 
	{
		strcpy(PatternArg, argv[optind]);
		optind += 1;
	}

	if (RemainingArgs < MinArgsRequired)
	{
		fprintf(stderr,"Error: Few arguments\n");
		PrintUsage();
		return 1;
	}

	static const int BufferSize = 1024 * 1024 * 1024;
	static char buffer[BufferSize];
	
	std::vector<Text> FileList;
	FileList.reserve(RemainingArgs);
	
	for (int FileIndex = optind; FileIndex < argc; FileIndex++)
	{
		FileList.emplace_back(argv[FileIndex]);
	}

	if (strcmp(AlgorithName, "") == 0)
		strcpy(AlgorithName, "boyer_moore");

	bool UsingSlidingWindow = strcmp(AlgorithName, "sliding_window") == 0;
	bool UsingKmp = strcmp(AlgorithName, "kmp") == 0;
	bool UsingBoyerMoore = strcmp(AlgorithName, "boyer_moore") == 0;
	bool UsingSellers = strcmp(AlgorithName, "sellers") == 0;
	bool UsingWuManber = strcmp(AlgorithName, "wu_manber") == 0;
	bool UsingAhoCorasick = strcmp(AlgorithName, "aho_corasick") == 0;

	const bool UsingSomeAlgorithm = UsingSlidingWindow + UsingKmp + UsingBoyerMoore + UsingSellers + UsingWuManber + UsingAhoCorasick;
	if (!UsingSomeAlgorithm)
	{
		fprintf(stderr,"Error: Algorithm not supported/found\n");
		PrintUsage();
		return 1;
	}

	static const std::map<Text, std::function<std::unique_ptr<SinglePatternSearch>()>> StrategySelector = 
	{
		{"sliding_window", []() -> std::unique_ptr<SlidingWindow> { return std::make_unique<SlidingWindow>(); }},
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
			if (Pattern.Length() == 0)
				continue;
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
	long long TotalLines = 0;

	// std::vector<size_t> SinglePatternOccurrences;
	// std::vector<std::pair<size_t, size_t>> MultiplePatternOccurrences;

	{
		// BenchmarkTimer bench;
		
		if (UsingAhoCorasick)
		{
			BenchmarkTimer bench;
			AhoCorasick::BuildFSM(PatternList);
		}

		for (const Text& File : FileList)
		{
			// BenchmarkTimer bench;
			FILE *fp = fopen(File.GetData(), "r");
			
			if (fp == NULL)
			{
				fprintf(stderr,"Warning: skiping file \"%s\", text file does not exist\n", File.GetData());
				continue;
			}

			while (fgets(buffer, BufferSize, fp))
			{
				Text text(buffer, BufferSize); // Borrow pointer
				bool HasOccurences = false;

				if (UsingAhoCorasick)
				{
					int MultiplePatternOccurrences = AhoCorasick::Search(text, PatternList, OptAhoCorasick);
					HasOccurences = MultiplePatternOccurrences != 0;
					TotalOccurrences += MultiplePatternOccurrences;
				}
				else 
				{
					for (int i = 0; i < PatternList.size(); i++)
					{
						int SinglePatternOccurrences = SearchStrategies[i]->Search(text, PatternList[i], EditDistance);
						HasOccurences |= SinglePatternOccurrences != 0;
						TotalOccurrences += SinglePatternOccurrences;
					}
				}

				if (HasOccurences && !PrintCount)
					printf("%s\n", buffer);
				if (HasOccurences)
					TotalLines += 1;
			}
			
			fclose(fp);
		}
	}
	
	if (PrintCount)
		printf("%lld occurences on %lld lines\n", TotalOccurrences, TotalLines);
	
	return 0;
}
