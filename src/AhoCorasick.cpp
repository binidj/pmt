#include "AhoCorasick.h"
#include <queue>
#include <iostream>

AhoCorasick::State::State()
{
	IsFinalState = false;
	Fail = 0;
	std::fill(GoTo, GoTo + ALPHABET_SIZE, -1);
	Occurences = nullptr;
}

std::vector<AhoCorasick::State> AhoCorasick::FSM = std::vector<State>();

void AhoCorasick::BuildFSM(const std::vector<Text>& PatternSet)
{
	BuildGoTo(PatternSet);
	BuildFail(PatternSet);
}

void AhoCorasick::BuildGoTo(const std::vector<Text>& PatternSet)
{
	int NextState = 1;

	for (int PatternIndex = 0; PatternIndex < PatternSet.size(); PatternIndex++)
	{
		const Text& Pattern = PatternSet[PatternIndex];

		int cur = 0, j = 0;

		while (j < Pattern.Length() && FSM[cur].GoTo[Pattern[j]] != -1)
		{
			cur = FSM[cur].GoTo[Pattern[j]];
			j++;
		}

		while (j < Pattern.Length())
		{
			cur = FSM[cur].GoTo[Pattern[j]] = NextState++;
			FSM.emplace_back();
			j++;
		}

		if (FSM[cur].Occurences == nullptr)
		{
			FSM[cur].Occurences = new std::vector<int>;
			(*FSM[cur].Occurences).reserve(128);
		}
		(*FSM[cur].Occurences).emplace_back(PatternIndex);
	}

	for (int CharIndex = 0; CharIndex < ALPHABET_SIZE; CharIndex++)
	{
		if (FSM[0].GoTo[CharIndex] == -1)
		{
			FSM[0].GoTo[CharIndex] = 0;
		}
	}
}

void AhoCorasick::BuildFail(const std::vector<Text>& PatternSet)
{
	std::queue<int> Queue;

	for (int CharIndex = 0; CharIndex < ALPHABET_SIZE; CharIndex++)
	{
		if (FSM[0].GoTo[CharIndex] > 0)
		{
			Queue.push(FSM[0].GoTo[CharIndex]);
			FSM[FSM[0].GoTo[CharIndex]].Fail = 0;
		}
	}

	while (!Queue.empty())
	{
		int CurrentState = Queue.front();
		Queue.pop();

		for (int CharIndex = 0; CharIndex < ALPHABET_SIZE; CharIndex++)
		{
			int Successor = FSM[CurrentState].GoTo[CharIndex];

			if (Successor >= 0)
			{			
				Queue.push(Successor);
				
				int Border = FSM[CurrentState].Fail;

				while (FSM[Border].GoTo[CharIndex] < 0)
				{
					Border = FSM[Border].Fail;
				}

				FSM[Successor].Fail = FSM[Border].GoTo[CharIndex];

				if (FSM[FSM[Successor].Fail].Occurences == nullptr)
					continue;

				if (FSM[Successor].Occurences == nullptr)
				{
					FSM[Successor].Occurences = new std::vector<int>;
					(*FSM[Successor].Occurences).reserve(128);
				}

				for (const int PatternIndex : *FSM[FSM[Successor].Fail].Occurences)
				{
					(*FSM[Successor].Occurences).emplace_back(PatternIndex);
				}
			}
		}
	}
}

const std::vector<std::pair<int, int>>& AhoCorasick::Search(const Text& text, const std::vector<Text>& PatternSet, const bool Rebuild)
{
	if (FSM.size() == 0 || Rebuild)
	{
		FSM.reserve(256);
		FSM.emplace_back();
		BuildFSM(PatternSet);
	}

	std::vector<std::pair<int, int>> OccurencesSet; // (PatternSet.size(), std::vector<size_t>());
	OccurencesSet.reserve(128);

	int cur = 0;

	for (int i = 0; i < text.Length(); i++)
	{
		while (FSM[cur].GoTo[text[i]] < 0)
		{
			cur = FSM[cur].Fail;
		}
		
		cur = FSM[cur].GoTo[text[i]];

		if (FSM[cur].Occurences == nullptr)
			continue;

		for (const int PatternIndex : *FSM[cur].Occurences)
		{
			OccurencesSet.emplace_back(PatternIndex, i - (int)PatternSet[PatternIndex].Length() + 1);
			// OccurencesSet[PatternIndex].emplace_back(i - (int)PatternSet[PatternIndex].Length() + 1);
		}
	}

	return OccurencesSet;
}