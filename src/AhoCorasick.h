#pragma once
#include "Text.h"
#include <vector>

const size_t ALPHA_SIZE = 128;

class AhoCorasick
{
private:
	struct State
	{
		bool IsFinalState;
		int Fail;
		int GoTo[ALPHA_SIZE];
		std::vector<int> Occurences;

		State();
	};

	static std::vector<State> FSM;

	static void BuildFSM(const std::vector<Text>& PatternSet);

	static void BuildGoTo(const std::vector<Text>& PatternSet);

	static void BuildFail(const std::vector<Text>& PatternSet);
	
public:
	// TODO: optimize this function
    static const std::vector<std::vector<size_t>> Search(const Text& text, const std::vector<Text>& PatternSet, const bool Rebuild = false);
};