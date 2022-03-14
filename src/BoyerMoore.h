#pragma once
#include <vector>
#include "Text.h"
#include "Constants.h"

class BoyerMoore
{
private:
    static std::vector<int> BadChar;
    static std::vector<int> GoodSuffix;
    static void GetBadChar(const Text& pattern);
    static void GetGoodSuffix(const Text& pattern);
public:
    static const std::vector<size_t>& Search(const Text& text, const Text& pattern, bool BuildHeuriscts = false);
};