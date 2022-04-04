#pragma once
#include "Text.h"
#include "Constants.h"
#include <vector>
#include <list>

class AhoCorasick
{
private:
	struct State
	{
		bool IsFinalState;
		int Fail;
		int GoTo[ALPHABET_SIZE];
		std::vector<int> Occurences;

		State();
	};

	static int CurrentOcc;
	static std::vector<State> FSM;
	static void BuildGoTo(const std::vector<Text>& PatternSet);
	static void BuildFail(const std::vector<Text>& PatternSet);
public:
    static std::vector<std::pair<size_t,size_t>> OccurenceSet;
	static void BuildFSM(const std::vector<Text>& PatternSet);
	static int Search(const Text& text, const std::vector<Text>& PatternSet, const bool OptMode);
};