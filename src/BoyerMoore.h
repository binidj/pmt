#pragma once
#include <vector>
#include "Text.h"
#include "Constants.h"
#include "SinglePatternSearch.h"

class BoyerMoore : public SinglePatternSearch
{
private:
    std::vector<int> BadChar;
    std::vector<int> GoodSuffix;
    void GetBadChar(const Text& pattern);
    void GetGoodSuffix(const Text& pattern);
    std::vector<int> GetBorder(const Text& pattern);
public:
    void Init(const Text& pattern, const int EditDistance);
    const int Search(const Text& text, const Text& pattern, const int EditDistance);
};