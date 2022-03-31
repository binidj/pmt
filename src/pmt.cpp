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
#include <unistd.h>
#include <map>

typedef const std::vector<size_t>(*SearchFunctionPointer)(const Text&, const Text&, const int, const bool);
typedef void(*InitFunctionPointer)(const Text&);


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

	bool UsingAhoCorasick = strcmp(AlgorithName, "aho_corasick") == 0;
	auto SinglePatternSearch = BoyerMoore::Search;
	// auto SinglePatternInit = BoyerMoore::Init;
	
	static std::map<Text, SearchFunctionPointer> SearchSelector = 
	{
		{"boyer_moore", BoyerMoore::Search},
		{"kmp", KMP::Search},
		{"sellers", Sellers::Search},
		{"wu_manber", WuManber::Search}
	};

	// static std::map<Text, InitFunctionPointer> InitSelector = 
	// {
	// 	{"boyer_moore", BoyerMoore::Init},
	// 	{"kmp", KMP::Init},
	// 	{"sellers", Sellers::Init},
	// 	{"wu_manber", WuManber::Init}
	// };

	if (!UsingAhoCorasick && strcmp(AlgorithName, "") != 0)
	{
		SinglePatternSearch = SearchSelector[Text(AlgorithName)];
		// SinglePatternInit = InitSelector[Text(AlgorithName)];

		if (SinglePatternSearch == nullptr)
		{
			fprintf(stderr,"Error: Algorithm not supported/found\n");
			PrintUsage();
			return 1;
		}
	}

	if ((SinglePatternSearch == Sellers::Search || SinglePatternSearch == WuManber::Search) && EditDistance < 0)
	{
		fprintf(stderr,"Error: You should provide a valid EditDistance\n");
		PrintUsage();
		return 1;
	}

	// // Ajeitar essa parte, seleção e erros separados
	// // AlgorithName so pode conter single pattern, usar aho corasick somente via flag -p
	// if (strcmp(AlgorithName, "boyer_moore") == 0) 
	// {
	// 	SinglePatternSearch = BoyerMoore::Search;
	// }
	// // se algoritmo for Sellers/WuManber e EditDistance < 0 : printa erro de distancia invalida
	// else if((strcmp(AlgorithName, "sellers") == 0 || strcmp(AlgorithName, "wu_manber") == 0) && EditDistance < 0 )
	// {
	// 	fprintf(stderr,"Invalid distance.\n");
	// }
	// // se algoritmo for WuManber dar erro quando tamanho do padrão > 64
	// else if(strcmp(AlgorithName, "wu_manber") == 0 && strlen(PatternFile) < 0) // errado, preciso verificar
	// {
	// 	fprintf(stderr,"Invalid pattern.\n");
	// }
	
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
		// FILE* fl = fopen(argv[FileIndex], "r");
		// Rodar a busca pros arquivos nos argumentos
		// fclose(fl);
	}

	std::vector<Text> PatternList;
	PatternList.reserve(1024);

	if (HasPatternFile)
	{
		FILE* fp = fopen(PatternFile, "r");
		if (fp == NULL)
		{
			fprintf(stderr,"Pattern file %s does not exist\n", argv[optind]);
			PrintUsage();
			return 1;
		}

		while (fgets(buffer, BufferSize, fp))
		{
			PatternList.emplace_back(PatternArg);
			if (SinglePatternSearch == WuManber::Search && PatternList.back().Length() > 64)
			{
				fprintf(stderr,"Warning: skiping search for \"%s\", wu_manber does not support large patterns.\n", PatternList.back().GetData());
				PatternList.pop_back();
			}
		}
	}
	else 
	{
		PatternList.emplace_back(PatternArg);
		if (SinglePatternSearch == WuManber::Search && PatternList.back().Length() > 64)
		{
			fprintf(stderr,"Warning: skiping search for \"%s\", wu_manber does not support large patterns.\n", PatternList.back().GetData());
			return 0;
		}
	}

	// FILE* fl = fopen(argv[optind], "r");
	// fl = fopen("./shakespeare_all_texts_lowercase.txt", "r");

	// if (fl == NULL)
	// {
	// 	fprintf(stderr,"File %s does not exist\n", argv[optind]);
	// 	// PrintUsage();
	// 	// return 1;
	// }

	// Organizar loop: Para toda FileList, percorrer toda a PatternList
	// Diferenciar SinglePatternSearch e Aho 

	size_t OccAmount = 0;

	

	{
		BenchmarkTimer benchmark;
		Text patt("coward");

		std::vector<Text> PatternSet = { "love", "death", "conscience", "romeo", "juliet" };
		// while (fgets(buffer, BufferSize, fl))
		{
			// printf("%s", buffer);
			Text text(buffer);
			
			std::vector<size_t>Occ = std::move(SinglePatternSearch(text, patt, EditDistance, false));
			// const std::vector<std::vector<size_t>> OccSet = AhoCorasick::Search(text, PatternSet);

			// other += Occ.size();
			
			// for (auto& vec : OccSet)
			// {
			// 	OccAmount += vec.size();
			// }
		}
	}

	printf("Found %zu occurences\n", OccAmount);
	// printf("%zu\n", other);

	// fclose(fl);
	
	return 0;
}
