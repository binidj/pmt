#pragma once
#include <vector>
#include "Text.h"
#include "Constants.h"
#include "SinglePatternSearch.h"

class BoyerMoore : SinglePatternSearch
{
private:
    std::vector<int> BadChar;
    std::vector<int> GoodSuffix;
    void GetBadChar(const Text& pattern);
    void GetGoodSuffix(const Text& pattern);
public:
    void Init(const Text& pattern, const int EditDistance);
    const std::vector<size_t> Search(const Text& text, const Text& pattern, const int EditDistance);
};